import os
import logging

import math
import random
import numpy as np
import matplotlib.pyplot as plt
from tqdm import trange

from collections import deque
from typing import (
    TYPE_CHECKING,
    Any,
    Callable,
    Deque,
    Dict,
    Generic,
    List,
    Optional,
    Sequence,
    Tuple,
    TypeVar,
    Union
)

# Cocotb
import cocotb
from cocotb.clock import Clock
from cocotb.simtime import get_sim_time
from cocotb.handle import LogicObject, ValueObjectBase
from cocotb.triggers import First, Event, FallingEdge, RisingEdge, ReadOnly, Trigger
from cocotb.types import Array, LogicArray, Range

if TYPE_CHECKING:
    from cocotb.task import Task

T = TypeVar("T")

class TileBufferModel:
    """Transaction-level model of module."""
    def __init__(
        self,
        name: str,
        POS_ADDRW: int,
        TILE_WIDTH:  int,
        TILE_HEIGHT: int,
        INITIAL_CLEAR_COLOR: LogicArray,
        INITIAL_CLEAR_DEPTH: LogicArray 
    ) -> None:
        self.name = name
        self.log = logging.getLogger(name)
        self.POS_ADDRW = POS_ADDRW
        self.TILE_WIDTH  = TILE_WIDTH
        self.TILE_HEIGHT = TILE_HEIGHT
        self.URAM_SIZE   = (self.TILE_WIDTH // 4) * self.TILE_HEIGHT
        self.URAM_ADDRW  = int(np.ceil(np.log2(self.URAM_SIZE)))

        self.INIT_CLEAR_COLOR = INITIAL_CLEAR_COLOR
        self.INIT_CLEAR_DEPTH = INITIAL_CLEAR_DEPTH

        self._output_callbacks = []

    def add_output_callback(self, callback) -> None:
        """Add callback to be called with output data when a transaction is produced."""
        self._output_callbacks.append(callback)

    def send_input(
        self, 
        data
    ) -> None:

        result_fixed = []
        self.log.debug("Sending output: %r", result_fixed)
        for cb in self._output_callbacks:
            cb(result_fixed)


class Testbench:
    """Reusable checker of module instance"""
    def __init__(
        self, 
        dut: Any, 
        name: Optional[str] = None
    ) -> None:

        self.dut = dut
        self.name = name if name is not None else type(self).__qualname__
        self.log = logging.getLogger(self.name)
        self.log.setLevel(logging.WARNING)

        self.POS_ADDRW   = int(self.dut.POS_ADDRW.value)
        self.TILE_WIDTH  = int(self.dut.TILE_WIDTH.value) 
        self.TILE_HEIGHT = int(self.dut.TILE_HEIGHT.value)
        self.URAM_SIZE   = (self.TILE_WIDTH // 4) * self.TILE_HEIGHT
        self.INITIAL_CLEAR_COLOR = self.dut.INITIAL_CLEAR_COLOR.value
        self.INITIAL_CLEAR_DEPTH = self.dut.INITIAL_CLEAR_DEPTH.value

        self._POS_ADDR_RANGE = Range(self.POS_ADDRW - 1, "downto", 0)

        self.clk_drv = Clock(self.dut.clk, 10, unit="ns")
        
        self.model = TileBufferModel(
            name=f"{self.name}.model",
            POS_ADDRW=self.POS_ADDRW,
            TILE_WIDTH=self.TILE_WIDTH,
            TILE_HEIGHT=self.TILE_HEIGHT,
            INITIAL_CLEAR_COLOR=self.INITIAL_CLEAR_COLOR,
            INITIAL_CLEAR_DEPTH=self.INITIAL_CLEAR_DEPTH
        )

    def start(self) -> None:
        self.clk_drv.start()

    def stop(self) -> None:
        self.clk_drv.stop()

    async def reset(self, cycles: int = 3) -> None:
        self.dut.rstn.value = 0
        for _ in range(cycles):
            await RisingEdge(self.dut.clk)
        self.dut.rstn.value = 1

    def get_bank_and_addr(self, x: int, y: int) -> Tuple[int, int]:
        """
        Get bank index and address for a given (x, y) coordinate.
        Banking by x % 4:
          Bank 0: x = 0, 4, 8, ...
          Bank 1: x = 1, 5, 9, ...
          Bank 2: x = 2, 6, 10, ...
          Bank 3: x = 3, 7, 11, ...
        
        Address within bank: y * (TILE_WIDTH / 4) + (x / 4)
        """
        bank = x % 4
        addr = y * (self.TILE_WIDTH // 4) + (x // 4)
        return bank, addr

    def read_pixel_direct(self, x: int, y: int) -> LogicArray:
        """Read a pixel directly from the appropriate URAM bank."""
        bank, addr = self.get_bank_and_addr(x, y)
        
        if bank == 0:
            return self.dut.URAM_BANK0[addr].value
        elif bank == 1:
            return self.dut.URAM_BANK1[addr].value
        elif bank == 2:
            return self.dut.URAM_BANK2[addr].value
        else:
            return self.dut.URAM_BANK3[addr].value

    async def write_2x2_quad(
        self,
        x: int,
        y: int,
        pixels: List[LogicArray],
        mask: int = 0b1111
    ) -> None:
        """
        Write a 2x2 quad at position (x, y).
        Takes 2 cycles: first row (y), then second row (y+1).
        
        pixels[0] = (x, y)
        pixels[1] = (x+1, y)
        pixels[2] = (x, y+1)
        pixels[3] = (x+1, y+1)
        
        mask bits correspond to pixels[0..3]
        """
        pos_addr_range = Range(self.POS_ADDRW - 1, "downto", 0)
        
        # Cycle 1: write top row (y)
        self.dut.i_write_x.value = LogicArray(x, pos_addr_range)
        self.dut.i_write_y.value = LogicArray(y, pos_addr_range)
        self.dut.i_pixel_data[0].value = pixels[0]
        self.dut.i_pixel_data[1].value = pixels[1]
        self.dut.i_write_mask.value = LogicArray(((mask >> 0) & 1) | (((mask >> 1) & 1) << 1), Range(1, "downto", 0))
        self.dut.i_write_valid.value = 1
        
        await self.clk_drv.cycles(1)
        
        # Cycle 2: write bottom row (y+1)
        self.dut.i_write_y.value = LogicArray(y + 1, pos_addr_range)
        self.dut.i_pixel_data[0].value = pixels[2]
        self.dut.i_pixel_data[1].value = pixels[3]
        self.dut.i_write_mask.value = LogicArray(((mask >> 2) & 1) | (((mask >> 3) & 1) << 1), Range(1, "downto", 0))
        
        await self.clk_drv.cycles(1)
        
        self.dut.i_write_valid.value = 0


@cocotb.test()
async def test(dut: Any) -> None:
    """Test module"""
    tb = Testbench(dut)
    tb.start()
    await tb.reset()

    await RisingEdge(tb.dut.o_clear_done)
    await tb.clk_drv.cycles(1)

    print(get_sim_time(unit="ns"))
    print(tb.dut.ready.value)

    # Check values of each bank after initial clear
    clear_color: LogicArray = tb.dut.INITIAL_CLEAR_COLOR.value
    clear_depth: LogicArray = tb.dut.INITIAL_CLEAR_DEPTH.value
    expected_value = LogicArray(str(clear_color) + str(clear_depth))
    print("Expected value clear: ", f"0x{int(str(expected_value), 2):018x}")

    for idx in range(tb.URAM_SIZE):
        assert tb.dut.URAM_BANK0[idx].value == expected_value, f"Bank0[{idx}] mismatch"
        assert tb.dut.URAM_BANK1[idx].value == expected_value, f"Bank1[{idx}] mismatch"
        assert tb.dut.URAM_BANK2[idx].value == expected_value, f"Bank2[{idx}] mismatch"
        assert tb.dut.URAM_BANK3[idx].value == expected_value, f"Bank3[{idx}] mismatch"

    print("Clearing finished with expected results")

    await tb.clk_drv.cycles(10)

    # Try clearing with different color
    color_range = Range(47, "downto", 0)
    clear_color: LogicArray = LogicArray(0x1B001C001D00, color_range)
    expected_value = LogicArray(str(clear_color) + str(clear_depth))
    print("Expected value triggered clear: ", f"0x{int(str(expected_value), 2):018x}")

    tb.dut.i_clear.value = 1
    tb.dut.i_clear_depth.value = clear_depth
    tb.dut.i_clear_color.value = clear_color
    await tb.clk_drv.cycles(1)
    tb.dut.i_clear.value = 0

    await RisingEdge(tb.dut.o_clear_done)
    await tb.clk_drv.cycles(1)

    print("Finished clearing with different color. Checking result...")

    for idx in range(tb.URAM_SIZE):
        assert tb.dut.URAM_BANK0[idx].value == expected_value, f"Bank0[{idx}] mismatch"
        assert tb.dut.URAM_BANK1[idx].value == expected_value, f"Bank1[{idx}] mismatch"
        assert tb.dut.URAM_BANK2[idx].value == expected_value, f"Bank2[{idx}] mismatch"
        assert tb.dut.URAM_BANK3[idx].value == expected_value, f"Bank3[{idx}] mismatch"

    print("Triggered clear finished with expected results")

    # Try writing to the tile (2x2 quads)
    color: LogicArray = LogicArray(0xff0011001100, color_range)
    write_value: LogicArray = LogicArray(str(color) + str(clear_depth))

    print("Testing writing to tile buffer")

    pos_addr_range = Range(7, "downto", 0)
    
    # Write diagonal pattern of 2x2 quads
    for i in range(0, tb.TILE_HEIGHT, 2):
        x = i % tb.TILE_WIDTH  # Wrap x to stay within tile
        if x % 2 != 0:
            x = x - 1  # Ensure x is even
        
        await tb.write_2x2_quad(
            x=x,
            y=i,
            pixels=[write_value, write_value, write_value, write_value],
            mask=0b1111
        )

    await tb.clk_drv.cycles(1)

    print("Finished writing to tile buffer")

    # Read out tile buffer directly from all 4 banks
    res = np.zeros((tb.TILE_HEIGHT, tb.TILE_WIDTH, 3), dtype=int)
    
    print("Reading from tile buffer directly as cocotb node")

    for y in range(tb.TILE_HEIGHT):
        for x in range(tb.TILE_WIDTH):
            val = tb.read_pixel_direct(x, y)
            val_str = str(val)[0:48]  # Get color portion (48 bits)
            rgb = [int(val_str[i:i+16], 2) >> 8 for i in range(0, 48, 16)]  # 16-bit per channel, take upper 8
            res[y][x] = rgb

    plt.imshow(res)
    plt.savefig("tile_buffer_direct_read.png")
    plt.show()

    # Read from tile buffer using interface
    print("Reading from tile buffer through RTL interface to check validity")
    
    for y in range(tb.TILE_HEIGHT):
        for x in range(0, tb.TILE_WIDTH, 4):
            tb.dut.i_read_x.value = LogicArray(x, pos_addr_range)
            tb.dut.i_read_y.value = LogicArray(y, pos_addr_range)
            tb.dut.i_read_valid.value = 1

            await tb.clk_drv.cycles(1)
            tb.dut.i_read_valid.value = 0
            await ReadOnly()

            assert tb.dut.o_read_valid.value == 1, f"o_read_valid not high at ({x}, {y})"
            
            # Extract RGB from each output
            def extract_rgb(val: LogicArray) -> List[int]:
                val_str = str(val)[0:48]
                return [int(val_str[i:i+16], 2) >> 8 for i in range(0, 48, 16)]
            
            rgb0 = extract_rgb(tb.dut.o_read_data[0].value)
            rgb1 = extract_rgb(tb.dut.o_read_data[1].value)
            rgb2 = extract_rgb(tb.dut.o_read_data[2].value)
            rgb3 = extract_rgb(tb.dut.o_read_data[3].value)

            for i in range(3):
                assert rgb0[i] == res[y][x][i], f"Pixel 0: Got {rgb0[i]} - expected {res[y][x][i]} at ({x}, {y}, ch{i})"
                assert rgb1[i] == res[y][x+1][i], f"Pixel 1: Got {rgb1[i]} - expected {res[y][x+1][i]} at ({x+1}, {y}, ch{i})"
                assert rgb2[i] == res[y][x+2][i], f"Pixel 2: Got {rgb2[i]} - expected {res[y][x+2][i]} at ({x+2}, {y}, ch{i})"
                assert rgb3[i] == res[y][x+3][i], f"Pixel 3: Got {rgb3[i]} - expected {res[y][x+3][i]} at ({x+3}, {y}, ch{i})"

            await tb.clk_drv.cycles(1)

    tb.dut.i_read_valid.value = 0
    await tb.clk_drv.cycles(1)

    print("Finished reading tile buffer through RTL interface and received expected results")

    # Test partial write mask
    print("Testing partial write mask")
    
    different_color: LogicArray = LogicArray(0x00FF00FF00FF, color_range)
    different_value: LogicArray = LogicArray(str(different_color) + str(clear_depth))
    
    # Write only pixels 0 and 3 of a 2x2 quad (diagonal)
    # With the new interface, we write row by row:
    # Row 0: pixel 0 (mask bit 0), pixel 1 (mask bit 1)
    # Row 1: pixel 2 (mask bit 0), pixel 3 (mask bit 1)
    # So mask 0b1001 becomes: row0 mask=0b01, row1 mask=0b10
    
    await tb.write_2x2_quad(
        x=0,
        y=0,
        pixels=[different_value, different_value, different_value, different_value],
        mask=0b1001  # Only pixels 0 and 3
    )
    
    await tb.clk_drv.cycles(1)
    
    # Verify: pixel (0,0) and (1,1) should have new color, (1,0) and (0,1) should have old color
    val_0_0 = tb.read_pixel_direct(0, 0)
    val_1_0 = tb.read_pixel_direct(1, 0)
    val_0_1 = tb.read_pixel_direct(0, 1)
    val_1_1 = tb.read_pixel_direct(1, 1)
    
    print(f"val_0_0: {val_0_0}")
    print(f"val_1_0: {val_1_0}")
    print(f"val_0_1: {val_0_1}")
    print(f"val_1_1: {val_1_1}")
    print(f"different_value: {different_value}")
    print(f"write_value: {write_value}")
    
    assert val_0_0 == different_value, f"Pixel (0,0) should have new value, got {val_0_0}"
    assert val_1_0 != different_value, f"Pixel (1,0) should have old value, got {val_1_0}"
    assert val_0_1 != different_value, f"Pixel (0,1) should have old value, got {val_0_1}"
    assert val_1_1 == different_value, f"Pixel (1,1) should have new value, got {val_1_1}"
    
    print("Partial write mask test passed")

    # Test writing at different x alignments
    print("Testing writes at different x alignments")
    
    color_align0: LogicArray = LogicArray(0xAA00BB00CC00, color_range)
    color_align2: LogicArray = LogicArray(0x110022003300, color_range)
    value_align0: LogicArray = LogicArray(str(color_align0) + str(clear_depth))
    value_align2: LogicArray = LogicArray(str(color_align2) + str(clear_depth))
    
    # Write at x=0 (x[1]=0, uses banks 0,1)
    await tb.write_2x2_quad(
        x=0,
        y=4,
        pixels=[value_align0, value_align0, value_align0, value_align0],
        mask=0b1111
    )
    
    # Write at x=2 (x[1]=1, uses banks 2,3)
    await tb.write_2x2_quad(
        x=2,
        y=4,
        pixels=[value_align2, value_align2, value_align2, value_align2],
        mask=0b1111
    )
    
    await tb.clk_drv.cycles(1)
    
    # Verify
    assert tb.read_pixel_direct(0, 4) == value_align0, "Pixel (0,4) wrong"
    assert tb.read_pixel_direct(1, 4) == value_align0, "Pixel (1,4) wrong"
    assert tb.read_pixel_direct(0, 5) == value_align0, "Pixel (0,5) wrong"
    assert tb.read_pixel_direct(1, 5) == value_align0, "Pixel (1,5) wrong"
    
    assert tb.read_pixel_direct(2, 4) == value_align2, "Pixel (2,4) wrong"
    assert tb.read_pixel_direct(3, 4) == value_align2, "Pixel (3,4) wrong"
    assert tb.read_pixel_direct(2, 5) == value_align2, "Pixel (2,5) wrong"
    assert tb.read_pixel_direct(3, 5) == value_align2, "Pixel (3,5) wrong"
    
    print("Different x alignment test passed")

    # Finish
    print("Finished test suite")
    await tb.clk_drv.cycles(10)
    tb.stop()
