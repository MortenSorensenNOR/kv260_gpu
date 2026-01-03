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
from cocotb.regression import TestFactory
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
        self.URAM_SIZE   = (self.TILE_WIDTH // 2) * (self.TILE_HEIGHT // 2)
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
        self.URAM_SIZE   = (self.TILE_WIDTH // 2) * (self.TILE_HEIGHT // 2)
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
        Banking by (X parity, Y parity):
          Bank 0: even X, even Y -> (0,0), (2,0), (0,2), ...
          Bank 1: odd X,  even Y -> (1,0), (3,0), (1,2), ...
          Bank 2: even X, odd Y  -> (0,1), (2,1), (0,3), ...
          Bank 3: odd X,  odd Y  -> (1,1), (3,1), (1,3), ...
        
        Address within bank: (y / 2) * (TILE_WIDTH / 2) + (x / 2)
        """
        x_parity = x & 1
        y_parity = y & 1
        bank = (y_parity << 1) | x_parity
        addr = (y >> 1) * (self.TILE_WIDTH // 2) + (x >> 1)
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
        Write a 2x2 quad at position (x, y). Both x and y must be even.
        Takes 1 cycle - all 4 pixels written simultaneously.
        
        pixels[0] = (x, y)     - Bank 0
        pixels[1] = (x+1, y)   - Bank 1
        pixels[2] = (x, y+1)   - Bank 2
        pixels[3] = (x+1, y+1) - Bank 3
        
        mask bits correspond to pixels[0..3]
        """
        assert x % 2 == 0, f"x must be even, got {x}"
        assert y % 2 == 0, f"y must be even, got {y}"
        
        pos_addr_range = Range(self.POS_ADDRW - 1, "downto", 0)
        
        self.dut.i_write_x.value = LogicArray(x, pos_addr_range)
        self.dut.i_write_y.value = LogicArray(y, pos_addr_range)
        self.dut.i_pixel_data[0].value = pixels[0]
        self.dut.i_pixel_data[1].value = pixels[1]
        self.dut.i_pixel_data[2].value = pixels[2]
        self.dut.i_pixel_data[3].value = pixels[3]
        self.dut.i_write_mask.value = LogicArray(mask, Range(3, "downto", 0))
        self.dut.i_write_valid.value = 1
        
        await self.clk_drv.cycles(1)
        
        self.dut.i_write_valid.value = 0

    async def read_2x2_quad(
        self,
        x: int,
        y: int
    ) -> List[LogicArray]:
        """
        Read a 2x2 quad at position (x, y). Both x and y must be even.
        Takes 1 cycle (plus 1 cycle latency for data).
        
        Returns:
          [0] = (x, y)     - Bank 0
          [1] = (x+1, y)   - Bank 1
          [2] = (x, y+1)   - Bank 2
          [3] = (x+1, y+1) - Bank 3
        """
        assert x % 2 == 0, f"x must be even, got {x}"
        assert y % 2 == 0, f"y must be even, got {y}"
        
        pos_addr_range = Range(self.POS_ADDRW - 1, "downto", 0)
        
        self.dut.i_read_x.value = LogicArray(x, pos_addr_range)
        self.dut.i_read_y.value = LogicArray(y, pos_addr_range)
        self.dut.i_read_valid.value = 1
        
        await self.clk_drv.cycles(1)
        
        self.dut.i_read_valid.value = 0
        await ReadOnly()
        
        assert self.dut.o_read_valid.value == 1, f"o_read_valid not high at ({x}, {y})"
        data = [
            self.dut.o_read_data[0].value,
            self.dut.o_read_data[1].value,
            self.dut.o_read_data[2].value,
            self.dut.o_read_data[3].value
        ]

        # Have to wait because we have used the ReadOnly() meaning we now cant write anything in this cycle (poor design
        # but works for now)
        await self.clk_drv.cycles(1)
        
        return data


def extract_rgb(val: LogicArray) -> List[int]:
    """Extract RGB values from a 72-bit pixel (48-bit color + 24-bit depth)."""
    val_str = str(val)[0:48]  # Get color portion (48 bits)
    return [int(val_str[i:i+16], 2) >> 8 for i in range(0, 48, 16)]


# Fixture to create and initialize testbench
async def get_initialized_tb(dut):
    """Create testbench, start clock, reset, and wait for initial clear."""
    tb = Testbench(dut)
    tb.start()
    await tb.reset()
    await RisingEdge(tb.dut.o_clear_done)
    await tb.clk_drv.cycles(1)
    return tb


@cocotb.test()
async def test_initial_clear(dut: Any) -> None:
    """Test that initial clear sets all banks to expected value."""
    tb = await get_initialized_tb(dut)
    
    clear_color: LogicArray = tb.dut.INITIAL_CLEAR_COLOR.value
    clear_depth: LogicArray = tb.dut.INITIAL_CLEAR_DEPTH.value
    expected_value = LogicArray(str(clear_color) + str(clear_depth))
    
    for idx in range(tb.URAM_SIZE):
        assert tb.dut.URAM_BANK0[idx].value == expected_value, f"Bank0[{idx}] mismatch"
        assert tb.dut.URAM_BANK1[idx].value == expected_value, f"Bank1[{idx}] mismatch"
        assert tb.dut.URAM_BANK2[idx].value == expected_value, f"Bank2[{idx}] mismatch"
        assert tb.dut.URAM_BANK3[idx].value == expected_value, f"Bank3[{idx}] mismatch"
    
    tb.log.info("Initial clear test passed")
    tb.stop()


@cocotb.test()
async def test_triggered_clear(dut: Any) -> None:
    """Test clearing with a different color via i_clear signal."""
    tb = await get_initialized_tb(dut)
    
    await tb.clk_drv.cycles(10)
    
    color_range = Range(47, "downto", 0)
    clear_depth: LogicArray = tb.dut.INITIAL_CLEAR_DEPTH.value
    clear_color: LogicArray = LogicArray(0x1B001C001D00, color_range)
    expected_value = LogicArray(str(clear_color) + str(clear_depth))
    
    tb.dut.i_clear.value = 1
    tb.dut.i_clear_depth.value = clear_depth
    tb.dut.i_clear_color.value = clear_color
    await tb.clk_drv.cycles(1)
    tb.dut.i_clear.value = 0
    
    await RisingEdge(tb.dut.o_clear_done)
    await tb.clk_drv.cycles(1)
    
    for idx in range(tb.URAM_SIZE):
        assert tb.dut.URAM_BANK0[idx].value == expected_value, f"Bank0[{idx}] mismatch"
        assert tb.dut.URAM_BANK1[idx].value == expected_value, f"Bank1[{idx}] mismatch"
        assert tb.dut.URAM_BANK2[idx].value == expected_value, f"Bank2[{idx}] mismatch"
        assert tb.dut.URAM_BANK3[idx].value == expected_value, f"Bank3[{idx}] mismatch"
    
    tb.log.info("Triggered clear test passed")
    tb.stop()


@cocotb.test()
async def test_write_2x2_quads(dut: Any) -> None:
    """Test writing 2x2 quads in diagonal pattern."""
    tb = await get_initialized_tb(dut)
    
    color_range = Range(47, "downto", 0)
    clear_depth: LogicArray = tb.dut.INITIAL_CLEAR_DEPTH.value
    color: LogicArray = LogicArray(0xff0011001100, color_range)
    write_value: LogicArray = LogicArray(str(color) + str(clear_depth))
    
    # Write diagonal pattern of 2x2 quads
    for i in range(0, tb.TILE_HEIGHT, 2):
        await tb.write_2x2_quad(
            x=i,
            y=i,
            pixels=[write_value, write_value, write_value, write_value],
            mask=0b1111
        )
    
    await tb.clk_drv.cycles(1)
    
    # Verify by reading directly
    for i in range(0, tb.TILE_HEIGHT, 2):
        for offset in [(0,0), (1,0), (0,1), (1,1)]:
            x, y = i + offset[0], i + offset[1]
            val = tb.read_pixel_direct(x, y)
            assert val == write_value, f"Pixel ({x},{y}) mismatch after write"
    
    tb.log.info("Write 2x2 quads test passed")
    tb.stop()


@cocotb.test()
async def test_read_2x2_interface(dut: Any) -> None:
    """Test reading via 2x2 quad interface matches direct reads."""
    tb = await get_initialized_tb(dut)
    
    color_range = Range(47, "downto", 0)
    clear_depth: LogicArray = tb.dut.INITIAL_CLEAR_DEPTH.value
    color: LogicArray = LogicArray(0xff0011001100, color_range)
    write_value: LogicArray = LogicArray(str(color) + str(clear_depth))
    
    # Write diagonal pattern
    for i in range(0, tb.TILE_HEIGHT, 2):
        await tb.write_2x2_quad(
            x=i, y=i,
            pixels=[write_value] * 4,
            mask=0b1111
        )
    
    await tb.clk_drv.cycles(1)
    
    # Build reference image from direct reads
    res = np.zeros((tb.TILE_HEIGHT, tb.TILE_WIDTH, 3), dtype=int)
    for y in range(tb.TILE_HEIGHT):
        for x in range(tb.TILE_WIDTH):
            val = tb.read_pixel_direct(x, y)
            res[y][x] = extract_rgb(val)
    
    # Read via interface and compare
    for y in range(0, tb.TILE_HEIGHT, 2):
        for x in range(0, tb.TILE_WIDTH, 2):
            quad = await tb.read_2x2_quad(x, y)
            
            for idx, (dx, dy) in enumerate([(0,0), (1,0), (0,1), (1,1)]):
                rgb = extract_rgb(quad[idx])
                for ch in range(3):
                    expected = res[y+dy][x+dx][ch]
                    assert rgb[ch] == expected, \
                        f"Quad pixel {idx} at ({x+dx},{y+dy}) ch{ch}: got {rgb[ch]}, expected {expected}"
    
    tb.log.info("Read 2x2 interface test passed")
    tb.stop()


@cocotb.test()
async def test_partial_write_mask(dut: Any) -> None:
    """Test partial write mask (only writing some pixels in a quad)."""
    tb = await get_initialized_tb(dut)
    
    color_range = Range(47, "downto", 0)
    clear_depth: LogicArray = tb.dut.INITIAL_CLEAR_DEPTH.value
    
    # First write all pixels with one color
    old_color: LogicArray = LogicArray(0xff0011001100, color_range)
    old_value: LogicArray = LogicArray(str(old_color) + str(clear_depth))
    
    await tb.write_2x2_quad(
        x=0, y=0,
        pixels=[old_value] * 4,
        mask=0b1111
    )
    
    await tb.clk_drv.cycles(1)
    
    # Now write with partial mask (only pixels 0 and 3)
    new_color: LogicArray = LogicArray(0x00FF00FF00FF, color_range)
    new_value: LogicArray = LogicArray(str(new_color) + str(clear_depth))
    
    await tb.write_2x2_quad(
        x=0, y=0,
        pixels=[new_value] * 4,
        mask=0b1001  # Only pixels 0 (x,y) and 3 (x+1,y+1)
    )
    
    await tb.clk_drv.cycles(1)
    
    # Verify via direct reads
    val_0_0 = tb.read_pixel_direct(0, 0)
    val_1_0 = tb.read_pixel_direct(1, 0)
    val_0_1 = tb.read_pixel_direct(0, 1)
    val_1_1 = tb.read_pixel_direct(1, 1)
    
    assert val_0_0 == new_value, "Pixel (0,0) should have new value (masked)"
    assert val_1_0 == old_value, "Pixel (1,0) should have old value (not masked)"
    assert val_0_1 == old_value, "Pixel (0,1) should have old value (not masked)"
    assert val_1_1 == new_value, "Pixel (1,1) should have new value (masked)"
    
    # Verify via read interface
    quad = await tb.read_2x2_quad(0, 0)
    assert quad[0] == new_value, "Read interface: pixel (0,0) should have new value"
    assert quad[1] == old_value, "Read interface: pixel (1,0) should have old value"
    assert quad[2] == old_value, "Read interface: pixel (0,1) should have old value"
    assert quad[3] == new_value, "Read interface: pixel (1,1) should have new value"
    
    tb.log.info("Partial write mask test passed")
    tb.stop()
