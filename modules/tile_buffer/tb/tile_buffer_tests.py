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

# utils (added to path by runner script)
# from cocotb_utils import Mailbox, DataValidDriver, DataValidMonitor, InOrderChecker

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
        self.URAM_SIZE   = self.TILE_WIDTH / 2 * self.TILE_HEIGHT
        self.URAM_ADDRW  = int(np.ceil(np.log2(self.URAM_SIZE)))

        self.INIT_CLEAR_COLOR = INITIAL_CLEAR_COLOR
        self.INIT_CLEAR_DEPTH = INITIAL_CLEAR_DEPTH

        # self._OUTPUT_RANGE = Range(self.DATA_WIDTH - 1, "downto", 0)
        # self._DOUBLE_OUTPUT_RANGE = Range(2*self.DATA_WIDTH - 1, "downto", 0)
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
        self.INITIAL_CLEAR_COLOR = self.dut.INITIAL_CLEAR_COLOR.value
        self.INITIAL_CLEAR_DEPTH = self.dut.INITIAL_CLEAR_DEPTH.value

        self._POS_ADDR_RANGE = Range(self.POS_ADDRW - 1, "downto", 0)

        self.clk_drv = Clock(self.dut.clk, 10, unit="ns")

        # self.input_drv = DataValidDriver(
        #     name=f"{self.name}.input_drv",
        #     clk=self.dut.clk,
        #     rstn=self.dut.rstn,
        #     valid=self.dut.i_dv,
        #     datas={
        #         "i_v0": self.dut.i_v0,
        #         "i_v1": self.dut.i_v1,
        #         "i_v2": self.dut.i_v2,
        #
        #         "i_attr_v0": self.dut.i_attr_v0,
        #         "i_attr_v1": self.dut.i_attr_v1,
        #         "i_attr_v2": self.dut.i_attr_v2,
        #     },
        #     initial_values={
        #         "i_v0": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
        #         "i_v1": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
        #         "i_v2": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
        #
        #         "i_attr_v0": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
        #         "i_attr_v1": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
        #         "i_attr_v2": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
        #     }
        # )
        #
        # self.input_monitor = DataValidMonitor(
        #     name=f"{self.name}.input_monitor",
        #     clk=self.dut.clk,
        #     rstn=self.dut.rstn,
        #     valid=self.dut.i_dv,
        #     datas={
        #         "i_v0": self.dut.i_v0, 
        #         "i_v1": self.dut.i_v1, 
        #         "i_v2": self.dut.i_v2, 
        #     },
        # )

        # self.input_monitor.add_callback(
        #     lambda datas: self.model.send_input(
        #         i_v0=datas["i_v0"],
        #         i_v1=datas["i_v1"],
        #         i_v2=datas["i_v2"],
        #     )
        # )
        
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
        # self.input_drv.start()
        # self.input_monitor.start()
        # cocotb.start_soon(self.fragment_capture()) # for dummy framebuffer
        
        # cocotb.start_soon(ready_driver(
        #     self.dut,
        #     ready=self.dut.i_ready,
        #     valid=self.dut.o_dv,
        #     clk=self.dut.clk,
        #     low_cycles=(4, 8)   # random backoff
        # ))

    def stop(self) -> None:
        self.clk_drv.stop()
        # self.input_drv.stop()
        # self.input_monitor.stop()

    async def reset(self, cycles: int = 3) -> None:
        self.dut.rstn.value = 0
        for _ in range(cycles):
            await RisingEdge(self.dut.clk)
        self.dut.rstn.value = 1


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

    # Check values of each 
    clear_color: LogicArray = tb.dut.INITIAL_CLEAR_COLOR.value
    clear_depth: LogicArray = tb.dut.INITIAL_CLEAR_DEPTH.value
    expected_value = LogicArray(str(clear_color) + str(clear_depth))
    print(expected_value)

    for y in range(tb.TILE_HEIGHT):
        for x in range(tb.TILE_WIDTH//2):
            idx = x + y * tb.TILE_WIDTH//2
            assert(tb.dut.URAM_BANK0[idx].value == expected_value)
            assert(tb.dut.URAM_BANK1[idx].value == expected_value)

    await tb.clk_drv.cycles(10)

    # Try clearing with different color
    color_range = Range(47, "downto", 0)
    clear_color: LogicArray = LogicArray(0x1B001C001D00, color_range)
    expected_value = LogicArray(str(clear_color) + str(clear_depth))
    print(expected_value)

    tb.dut.i_clear.value = 1
    tb.dut.i_clear_depth.value = clear_depth
    tb.dut.i_clear_color.value = clear_color
    await tb.clk_drv.cycles(1)
    tb.dut.i_clear.value = 0

    await RisingEdge(tb.dut.o_clear_done)
    await tb.clk_drv.cycles(1)

    for y in range(tb.TILE_HEIGHT):
        for x in range(tb.TILE_WIDTH//2):
            idx = x + y * tb.TILE_WIDTH//2
            assert(tb.dut.URAM_BANK0[idx].value == expected_value)
            assert(tb.dut.URAM_BANK1[idx].value == expected_value)

    # Try writing to the tile
    color: LogicArray = LogicArray(0xff0011001100, color_range)
    write_value: LogicArray = LogicArray(str(color) + str(clear_depth))

    pos_addr_range = Range(7, "downto", 0)
    for i in range(0, tb.TILE_HEIGHT, 2):
        tb.dut.i_write_x.value = LogicArray(i, pos_addr_range)
        tb.dut.i_write_y.value = LogicArray(i, pos_addr_range)
        print(f"Writing to ({i}, {i})")

        tb.dut.i_pixel_data[0].value = write_value
        tb.dut.i_pixel_data[1].value = write_value
        tb.dut.i_pixel_data[2].value = write_value
        tb.dut.i_pixel_data[3].value = write_value
        tb.dut.i_write_mask.value = LogicArray(0b1111, Range(3, "downto", 0))
        tb.dut.i_write_valid.value = 1

        await tb.clk_drv.cycles(1)

    tb.dut.i_write_valid.value = 0
    await tb.clk_drv.cycles(1)

    # Read out tile buffer directly
    res = np.zeros((tb.TILE_HEIGHT, tb.TILE_WIDTH, 3), dtype=int)

    BANK0 = np.zeros((tb.TILE_HEIGHT, tb.TILE_WIDTH//2, 3), dtype=int)
    BANK1 = np.zeros((tb.TILE_HEIGHT, tb.TILE_WIDTH//2, 3), dtype=int)
    for y in range(tb.TILE_HEIGHT):
        for x in range(tb.TILE_WIDTH//2):
            idx  = x + y * tb.TILE_WIDTH//2
            val0 = str(tb.dut.URAM_BANK0[idx].value)[0:48]
            val1 = str(tb.dut.URAM_BANK1[idx].value)[0:48]

            rgb0 = [int(val0[i:i+8], 2) for i in range(0, 48, 16)]
            rgb1 = [int(val1[i:i+8], 2) for i in range(0, 48, 16)]

            BANK0[y][x] = rgb0
            BANK1[y][x] = rgb1

    res[:, 0::2] = BANK0  # Even columns (0, 2, 4, ...)
    res[:, 1::2] = BANK1  # Odd columns (1, 3, 5, ...)

    # Read from tile buffer using interface
    # Not ideal rn since it is not in hardware and I cant be arsed to do the parallel process thing 
    for y in range(tb.TILE_HEIGHT):
        for x in range(0, tb.TILE_WIDTH, 4):
            tb.dut.i_read_x.value = LogicArray(x, pos_addr_range)
            tb.dut.i_read_y.value = LogicArray(y, pos_addr_range)
            tb.dut.i_read_valid.value = 1

            await tb.clk_drv.cycles(1)
            tb.dut.i_read_valid.value = 0
            await ReadOnly()

            assert(tb.dut.o_read_valid.value == 1)
            val0 = str(tb.dut.o_read_data[0].value)[0:48]
            val1 = str(tb.dut.o_read_data[1].value)[0:48]
            val2 = str(tb.dut.o_read_data[2].value)[0:48]
            val3 = str(tb.dut.o_read_data[3].value)[0:48]

            rgb0 = [int(val0[i:i+8], 2) for i in range(0, 48, 16)]
            rgb1 = [int(val1[i:i+8], 2) for i in range(0, 48, 16)]
            rgb2 = [int(val2[i:i+8], 2) for i in range(0, 48, 16)]
            rgb3 = [int(val3[i:i+8], 2) for i in range(0, 48, 16)]

            for i in range(3):
                assert(rgb0[i] == res[y][x][i])
                assert(rgb1[i] == res[y][x+1][i])
                assert(rgb2[i] == res[y][x+2][i])
                assert(rgb3[i] == res[y][x+3][i])

            await tb.clk_drv.cycles(1)

    tb.dut.i_read_valid.value = 0
    await tb.clk_drv.cycles(1)

    # Finish
    await tb.clk_drv.cycles(10)
    tb.stop()
