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

# utils (added to path by runner script)
from cocotb_utils import Mailbox, DataValidDriver, DataValidMonitor, InOrderChecker

if TYPE_CHECKING:
    from cocotb.task import Task

T = TypeVar("T")

class RasterizerFrontendModel:
    """Transaction-level model of module."""
    def __init__(
        self,
        name: str,
        FRAC_BITS: int,
        INT_BITS:  int,
        SCREEN_WIDTH: int,
        SCREEN_HEIGHT: int
    ) -> None:
        self.name = name
        self.log = logging.getLogger(name)
        self.FRAC_BITS = FRAC_BITS
        self.INT_BITS  = INT_BITS
        self.DATA_WIDTH = self.FRAC_BITS + self.INT_BITS
        self.SCREEN_WIDTH = SCREEN_WIDTH
        self.SCREEN_HEIGHT = SCREEN_HEIGHT

        self._OUTPUT_RANGE = Range(self.DATA_WIDTH - 1, "downto", 0)
        self._DOUBLE_OUTPUT_RANGE = Range(2*self.DATA_WIDTH - 1, "downto", 0)
        self._output_callbacks = []

    def add_output_callback(self, callback) -> None:
        """Add callback to be called with output data when a transaction is produced."""
        self._output_callbacks.append(callback)

    def triangle_fp_to_float(self, triangle: List[List[LogicArray]]) -> List[List[float]]:
        triangle_float = [[float(fp(bin(e), True, self.INT_BITS, self.FRAC_BITS)) for e in point] for point in triangle]
        return triangle_float

    def triangle_float_to_fp(self, triangle: List[List[float]]):
        triangle_fp = [[fp(e, True, self.INT_BITS, self.FRAC_BITS) for e in point] for point in triangle]
        triangle_la = [[LogicArray(e.bits, self._OUTPUT_RANGE) for e in point] for point in triangle_fp]
        return triangle_la

    def float_to_fp(self, val, signed, m, n, range):
        val_fp = fp(val, signed, m, n)
        val_la = LogicArray(val_fp.bits, range)
        return val_la

    def send_input(
        self, 
        i_v0: List[LogicArray],
        i_v1: List[LogicArray],
        i_v2: List[LogicArray]
    ) -> None:

        # TODO
        result_fixed = []
        self.log.debug("Sending output: %r", result_fixed)
        for cb in self._output_callbacks:
            cb(result_fixed)

class Testbench:
    """Reusable checker of module instance"""
    def __init__(self, dut: Any, name: Optional[str] = None) -> None:
        self.dut = dut
        self.name = name if name is not None else type(self).__qualname__
        self.log = logging.getLogger(self.name)
        self.log.setLevel(logging.WARNING)

        # TODO: More stuff
        self.SCREEN_WIDTH  = int(self.dut.SCREEN_WIDTH.value)
        self.SCREEN_HEIGHT = int(self.dut.SCREEN_HEIGHT.value)
        self.FRAC_BITS  = int(self.dut.FRAC_BITS.value)
        self.INT_BITS   = int(self.dut.INT_BITS.value)
        self.DATA_WIDTH = self.FRAC_BITS + self.INT_BITS
        self._OUTPUT_RANGE = Range(self.DATA_WIDTH - 1, "downto", 0)
        print(f"Data width: {self.DATA_WIDTH}")

        # --- Framebuffer: H x W x 3 (RGB), float in [0,1] ---
        self.framebuffer = np.zeros(
            (self.SCREEN_HEIGHT, self.SCREEN_WIDTH, 3),
            dtype=np.float32
        )

        self.clk_drv = Clock(self.dut.clk, 10, unit="ns")

        self.input_drv = DataValidDriver(
            name=f"{self.name}.input_drv",
            clk=self.dut.clk,
            rstn=self.dut.rstn,
            valid=self.dut.i_dv,
            datas={
                "i_v0": self.dut.i_v0,
                "i_v1": self.dut.i_v1,
                "i_v2": self.dut.i_v2,

                "i_attr_v0": self.dut.i_attr_v0,
                "i_attr_v1": self.dut.i_attr_v1,
                "i_attr_v2": self.dut.i_attr_v2,
            },
            initial_values={
                "i_v0": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
                "i_v1": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
                "i_v2": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],

                "i_attr_v0": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
                "i_attr_v1": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
                "i_attr_v2": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
            }
        )
        
        self.model = RasterizerFrontendModel(
            name=f"{self.name}.model",
            FRAC_BITS=self.FRAC_BITS,
            INT_BITS=self.INT_BITS,
            SCREEN_WIDTH=self.SCREEN_WIDTH,
            SCREEN_HEIGHT=self.SCREEN_HEIGHT
        )

    def clear_framebuffer(self, color: Tuple[float, float, float] = (0.0, 0.0, 0.0)) -> None:
        """Clear framebuffer to a given RGB color in [0,1]."""
        r, g, b = color
        self.framebuffer[:, :, 0] = r
        self.framebuffer[:, :, 1] = g
        self.framebuffer[:, :, 2] = b

    def start(self) -> None:
        self.clk_drv.start()
        self.input_drv.start()
        cocotb.start_soon(self.fragment_capture()) # for dummy framebuffer

    def stop(self) -> None:
        self.clk_drv.stop()
        self.input_drv.stop()

    async def reset(self, cycles: int = 3) -> None:
        self.clear_framebuffer()

        self.dut.rstn.value = 0
        for _ in range(cycles):
            await RisingEdge(self.dut.clk)
        self.dut.rstn.value = 1

    async def fragment_capture(self) -> None:
        """Capture output fragments into the framebuffer."""
        INT_BITS  = self.INT_BITS
        FRAC_BITS = self.FRAC_BITS

        while True:
            await RisingEdge(self.dut.clk)
            if int(self.dut.o_dv.value) == 0:
                continue

            x_val = fp(bin(self.dut.o_fragment_x.value), True, INT_BITS, FRAC_BITS)
            y_val = fp(bin(self.dut.o_fragment_y.value), True, INT_BITS, FRAC_BITS)
            x, y = int(x_val), int(y_val)
            if not (0 <= x < self.SCREEN_WIDTH and 0 <= y < self.SCREEN_HEIGHT):
                continue

            rgb = []
            for c in range(3):
                attr_fp = fp(
                    bin(self.dut.o_fragment_attr[c+1].value),
                    # bin(self.dut.o_fragment_attr[0].value),
                    True, INT_BITS, FRAC_BITS
                )
                rgb.append(float(attr_fp))
            # rgb = [1.0, 1.0, 1.0]
            self.framebuffer[y, x, :] = rgb

    def show_framebuffer(self, title: str = "Framebuffer") -> None:
        plt.figure()
        plt.imshow(np.clip(self.framebuffer, 0.0, 1.0))
        plt.title(title)
        plt.axis("off")
        plt.show()

def color_to_fp_rgb(tb, color):
    r, g, b = color
    INT_BITS  = tb.INT_BITS
    FRAC_BITS = tb.FRAC_BITS
    rng       = tb._OUTPUT_RANGE

    return [LogicArray(fp(r, True, INT_BITS, FRAC_BITS).bits, rng), LogicArray(fp(g, True, INT_BITS, FRAC_BITS).bits, rng), LogicArray(fp(b, True, INT_BITS, FRAC_BITS).bits, rng)]

@cocotb.test()
async def test(dut: Any) -> None:
    """Test module"""
    tb = Testbench(dut)
    tb.start()
    await tb.reset()

    tb.dut.i_ready.value = 1

    v0_color = (1.0, 0.0, 0.0)   # red
    v1_color = (0.0, 1.0, 0.0)   # green
    v2_color = (0.0, 0.0, 1.0)   # blue
    triangle = [[0.5, 0.0, 0.1], [0.0, 1.0, 0.5], [1.0, 1.0, 1.0]]
    for i in range(3):
        triangle[i][0] *= tb.SCREEN_WIDTH
        triangle[i][1] *= tb.SCREEN_HEIGHT

    triangle_fp = tb.model.triangle_float_to_fp(triangle)
    v0_attr = color_to_fp_rgb(tb, v0_color)
    v1_attr = color_to_fp_rgb(tb, v1_color)
    v2_attr = color_to_fp_rgb(tb, v2_color)

    tb.input_drv.send({
        "i_v0": triangle_fp[0],
        "i_v1": triangle_fp[1],
        "i_v2": triangle_fp[2],

        "i_attr_v0": v0_attr,
        "i_attr_v1": v1_attr,
        "i_attr_v2": v2_attr,
    })

    await First(
        RisingEdge(tb.dut.culled_triangle),
        RisingEdge(tb.dut.done)
    )
    if (tb.dut.culled_triangle.value == 1):
        print("This triangle was invalid and therefore culled")
    
    await tb.clk_drv.cycles(5)
    tb.stop()

    tb.show_framebuffer("Rasterized triangle")

