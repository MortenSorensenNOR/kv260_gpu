import os
import logging

import math
import random
import numpy as np
from tqdm import trange
import fixedpoint
from fixedpoint import FixedPoint as fp
import matplotlib.pyplot as plt

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
from cocotb.handle import LogicObject, ValueObjectBase
from cocotb.triggers import First, Event, FallingEdge, RisingEdge, ReadOnly, Trigger
from cocotb.types import Array, LogicArray, Range

if TYPE_CHECKING:
    from cocotb.task import Task

T = TypeVar("T")

class RasterizerFrontendModel:
    """Transaction-level model of module."""
    def __init__(
        self,
        name: str,
        POS_ADDRW   = 8,
        TILE_WIDTH  = 128,
        TILE_HEIGHT = 128,
        BURST_SIZE  = 64,
    ) -> None:
        self.name = name
        self.log = logging.getLogger(name)

        self.BURST_BITS  = int(np.ceil(np.log2(BURST_SIZE)))
        self.POS_ADDRW   = POS_ADDRW
        self.TILE_WIDTH  = TILE_WIDTH 
        self.TILE_HEIGHT = TILE_HEIGHT
        self.BURST_SIZE  = BURST_SIZE 
        self._output_callbacks = []

    def add_output_callback(self, callback) -> None:
        """Add callback to be called with output data when a transaction is produced."""
        self._output_callbacks.append(callback)

    def float_to_fp(self, val, signed, m, n, range):
        val_fp = fp(val, signed, m, n)
        val_la = LogicArray(val_fp.bits, range)
        return val_la

    def send_input(
        self, 
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
        clear_color: Tuple[float, float, float],
        name: Optional[str] = None
    ) -> None:
        self.dut = dut
        self.name = name if name is not None else type(self).__qualname__
        self.log = logging.getLogger(self.name)
        self.log.setLevel(logging.WARNING)

        self.clear_color = clear_color
        self.BURST_BITS  = int(dut.BURST_BITS.value)
        self.POS_ADDRW   = int(dut.POS_ADDRW.value)
        self.TILE_WIDTH  = int(dut.TILE_WIDTH.value)
        self.TILE_HEIGHT = int(dut.TILE_HEIGHT.value)
        self.BURST_SIZE  = int(dut.BURST_SIZE.value)

        self.TILE_DWIDTH = 72
        self._TILE_RANGE = Range(self.TILE_DWIDTH-1, "downto", 0)

        self.XRGB_WIDTH = 32
        self._XRGB_RANGE = Range(self.XRGB_WIDTH-1, "downto", 0)

        self.AXI_DWIDTH = 128
        self._AXI_RANGE = Range(self.AXI_DWIDTH-1, "downto", 0)

        # --- Framebuffer: H x W x 3 (RGB), float in [0,1] ---
        self.tile_buffer = np.array([
            [LogicArray(0, self.TILE_DWIDTH) for _ in range(self.TILE_WIDTH)]
            for _ in range(self.TILE_HEIGHT)
        ], dtype=LogicArray)

        self.clk_drv = Clock(self.dut.clk, 10, unit="ns")

    def clear_tilebuffer(self, color: Tuple[float, float, float] = (0.0, 0.0, 0.0), depth = "0xFFFFFF") -> None:
        """Clear framebuffer to a given RGB color in [0,1]."""
        r, g, b = color
        r_fp = fp(r, False, 8, 8)
        g_fp = fp(g, False, 8, 8)
        b_fp = fp(b, False, 8, 8)
        d_fp = fp(depth, False, 0, 24)
        rgbd_fp = fp("0x" + str(r_fp) + str(g_fp) + str(b_fp) + str(d_fp), False, 72, 0)

        value = LogicArray(int(rgbd_fp), self._TILE_RANGE)
        self.tile_buffer[:, :] = value

    def write_tilebuffer(self, x, y, color, depth = "0xFFFFFF") -> None:
        r, g, b = color
        r_fp = fp(r, False, 8, 8)
        g_fp = fp(g, False, 8, 8)
        b_fp = fp(b, False, 8, 8)
        d_fp = fp(depth, False, 0, 24)
        rgbd_fp = fp("0x" + str(r_fp) + str(g_fp) + str(b_fp) + str(d_fp), False, 72, 0)
        value = LogicArray(int(rgbd_fp), self._TILE_RANGE)
        self.tile_buffer[y][x] = value

    def start(self) -> None:
        self.clk_drv.start()

    def stop(self) -> None:
        self.clk_drv.stop()

    async def reset(self, cycles: int = 3) -> None:
        self.clear_tilebuffer(self.clear_color)

        self.dut.rstn.value = 0
        for _ in range(cycles):
            await RisingEdge(self.dut.clk)
        self.dut.rstn.value = 1

    def show_framebuffer(self, title: str = "Framebuffer") -> None:
        tile_buffer_rgb = np.zeros((self.TILE_HEIGHT, self.TILE_WIDTH, 3))
        for i in range(self.TILE_HEIGHT):
            for j in range(self.TILE_WIDTH):
                rgbd = LogicArray(self.tile_buffer[i][j], self._TILE_RANGE)
                r = int(rgbd[71:64]) / 255.0
                g = int(rgbd[55:48]) / 255.0
                b = int(rgbd[39:32]) / 255.0
                tile_buffer_rgb[i][j] = [r, g, b]

        plt.figure()
        plt.imshow(np.clip(tile_buffer_rgb, 0.0, 1.0))
        plt.title(title)
        plt.show()


@cocotb.test()
async def test_triangle(dut: Any) -> None:
    """Test module"""
    clear_color = (27, 28, 29)
    tb = Testbench(dut, clear_color)
    tb.start()
    await tb.reset()

    # Something visually interesting
    color = (255, 0, 0)
    for i in range(0, tb.TILE_HEIGHT, 2):
        tb.write_tilebuffer(i, i, color)
        tb.write_tilebuffer(i+1, i, color)
        tb.write_tilebuffer(i, i+1, color)
        tb.write_tilebuffer(i+1, i+1, color)
    # tb.show_framebuffer(f"Tile buffer")

    # start writeback
    print("Starting writeback...")
    tb.dut.i_read_ready.value = 1
    tb.dut.i_write_ready.value = 1
    tb.dut.writeback_start.value = 1
    await tb.clk_drv.cycles(1)
    tb.dut.writeback_start.value = 0

    await RisingEdge(tb.dut.writeback_done)
    # await tb.clk_drv.cycles(1000)
    # await RisingEdge(tb.dut.o_write_valid)
    # await tb.clk_drv.cycles(100)

    await tb.clk_drv.cycles(10)
    tb.stop()

