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
        AREA_FRAC_BITS: int,
        SCREEN_WIDTH: int,
        SCREEN_HEIGHT: int
    ) -> None:
        self.name = name
        self.log = logging.getLogger(name)
        self.FRAC_BITS = FRAC_BITS
        self.INT_BITS  = INT_BITS
        self.DATA_WIDTH = self.FRAC_BITS + self.INT_BITS
        self.AREA_FRAC_BITS = AREA_FRAC_BITS
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

        """Send data to the output and evaluate the model."""
        triangle_list = [i_v0, i_v1, i_v2]
        self.log.debug("Received input:\n  triangles: %r", triangle_list)

        # Turn fixed point into float
        triangle_list_float = self.triangle_fp_to_float(triangle_list)
        print(triangle_list_float)

        # Compute expected output
        v1, v2, v3 = triangle_list_float

        def compute_bounding_box(v1, v2, v3, screen_width, screen_height):
            min_x = max(min(v1[0], v2[0], v3[0]), 0)
            max_x = min(max(v1[0], v2[0], v3[0]), screen_width)
            min_y = max(min(v1[1], v2[1], v3[1]), 0)
            max_y = min(max(v1[1], v2[1], v3[1]), screen_height)
            min_x, min_y = int(min_x), int(min_y)
            max_x, max_y = int(np.ceil(max_x)), int(np.ceil(max_y))
            return min_x, max_x, min_y, max_y

        min_x, max_x, min_y, max_y = compute_bounding_box(v1, v2, v3, self.SCREEN_WIDTH, self.SCREEN_HEIGHT)

        # Compute the edge functions at the top-left corner of bounding box
        def edge_function(v1, v2, point):
            return (point[0] - v1[0]) * (v2[1] - v1[1]) - (point[1] - v1[1]) * (v2[0] - v1[0])

        e1 = edge_function(v1, v2, (min_x, min_y))
        e2 = edge_function(v2, v3, (min_x, min_y))
        e3 = edge_function(v3, v1, (min_x, min_y))

        # Precompute the edge function increments
        e1_dx = v2[1] - v1[1]
        e1_dy = -(v2[0] - v1[0])

        e2_dx = v3[1] - v2[1]
        e2_dy = -(v3[0] - v2[0])

        e3_dx = v1[1] - v3[1]
        e3_dy = -(v1[0] - v3[0])

        area = edge_function(v1, v2, v3) 
        should_be_culled = 0
        if (area <= 0.0001):
            print("area is negative, should be culled")
            should_be_culled = 1
            return

        # Compute barycentric weights at top-left corner of bounding box
        area_reciprocal = 1 / area

        print("area:     ", fp(area, True, self.DATA_WIDTH - self.AREA_FRAC_BITS, self.AREA_FRAC_BITS), area)
        print("area inv: ", fp(area_reciprocal, True, self.AREA_FRAC_BITS, self.DATA_WIDTH - self.AREA_FRAC_BITS), area_reciprocal)
        print()

        print("e1: ", fp(e1, True, self.DATA_WIDTH - self.AREA_FRAC_BITS, self.AREA_FRAC_BITS), e1)
        print("e2: ", fp(e2, True, self.DATA_WIDTH - self.AREA_FRAC_BITS, self.AREA_FRAC_BITS), e2)
        print("e3: ", fp(e3, True, self.DATA_WIDTH - self.AREA_FRAC_BITS, self.AREA_FRAC_BITS), e3)
        print()

        w1 = e2 * area_reciprocal
        w2 = e3 * area_reciprocal
        w3 = e1 * area_reciprocal

        # Increments for barycentric weights (same remap)
        w1_dx = e2_dx * area_reciprocal
        w1_dy = e2_dy * area_reciprocal

        w2_dx = e3_dx * area_reciprocal
        w2_dy = e3_dy * area_reciprocal

        w3_dx = e1_dx * area_reciprocal
        w3_dy = e1_dy * area_reciprocal

        # Initialize z at the top-left corner
        z = (w1 * v1[2]) + (w2 * v2[2]) + (w3 * v3[2])

        # Compute z increments
        z_dx = (w1_dx * v1[2]) + (w2_dx * v2[2]) + (w3_dx * v3[2])
        z_dy = (w1_dy * v1[2]) + (w2_dy * v2[2]) + (w3_dy * v3[2])

        result_fixed = []
        self.log.debug("Sending output: %r", result_fixed)
        for cb in self._output_callbacks:
            cb(result_fixed)

class Testbench:
    """Reusable checker of module instance"""
    def __init__(self, dut: Any, SCREEN_WIDTH, SCREEN_HEIGHT, name: Optional[str] = None) -> None:
        self.dut = dut
        self.name = name if name is not None else type(self).__qualname__
        self.log = logging.getLogger(self.name)
        self.log.setLevel(logging.WARNING)

        # TODO: More stuff
        self.SCREEN_WIDTH  = SCREEN_WIDTH  
        self.SCREEN_HEIGHT = SCREEN_HEIGHT 
        self.FRAC_BITS  = int(self.dut.FRAC_BITS.value)
        self.INT_BITS   = int(self.dut.INT_BITS.value)
        self.DATA_WIDTH = self.FRAC_BITS + self.INT_BITS
        self.AREA_FRAC_BITS = int(self.dut.AREA_FRAC_BITS.value)
        self._OUTPUT_RANGE = Range(self.DATA_WIDTH - 1, "downto", 0)

        # --- Framebuffer: H x W x 3 (RGB), float in [0,1] ---
        self.framebuffer = np.zeros(
            (self.SCREEN_HEIGHT, self.SCREEN_WIDTH, 3),
            dtype=np.float32
        )
        self.depthbuffer = np.ones(
            (self.SCREEN_HEIGHT, self.SCREEN_WIDTH),
            dtype=np.float32
        )

        self.clk_drv = Clock(self.dut.clk, 10, unit="ns")

        self.cmd_drv = DataValidDriver(
            name=f"{self.name}.cmd_drv",
            clk=self.dut.clk,
            rstn=self.dut.rstn,
            valid=self.dut.cmd_valid,
            datas={
                "cmd": self.dut.cmd,
            },
            initial_values={
                "cmd": LogicArray(0, self._OUTPUT_RANGE)
            }
        )

        self.model = RasterizerFrontendModel(
            name=f"{self.name}.model",
            FRAC_BITS=self.FRAC_BITS,
            INT_BITS=self.INT_BITS,
            AREA_FRAC_BITS=self.AREA_FRAC_BITS,
            SCREEN_WIDTH=self.SCREEN_WIDTH,
            SCREEN_HEIGHT=self.SCREEN_HEIGHT
        )


    def clear_framebuffer(self, color: Tuple[float, float, float] = (0.0, 0.0, 0.0)) -> None:
        """Clear framebuffer to a given RGB color in [0,1]."""
        r, g, b = color
        self.framebuffer[:, :, 0] = r
        self.framebuffer[:, :, 1] = g
        self.framebuffer[:, :, 2] = b
        self.depthbuffer[:, :] = 1.0

    def start(self) -> None:
        self.clk_drv.start()
        self.cmd_drv.start()
        # cocotb.start_soon(self.fragment_capture()) # for dummy framebuffer

    def stop(self) -> None:
        self.clk_drv.stop()
        self.cmd_drv.stop()

    async def reset(self, cycles: int = 3) -> None:
        self.clear_framebuffer()

        self.dut.rstn.value = 0
        for _ in range(cycles):
            await RisingEdge(self.dut.clk)
        self.dut.rstn.value = 1

    async def measure_cycles_for_current_triangle(self) -> int:
        """
        Measure number of clock cycles from input handshake
        (i_dv & i_ready) until done or culled_triangle is asserted.
        """
        # Wait for the input transaction to be accepted
        while True:
            await RisingEdge(self.dut.clk)
            if int(self.dut.i_dv.value) and int(self.dut.i_ready.value):
                break

        # Count cycles until triangle is either done or culled
        cycles = 0
        while True:
            await RisingEdge(self.dut.clk)
            cycles += 1
            if int(self.dut.done.value) or int(self.dut.culled_triangle.value):
                break

        return cycles

    async def fragment_capture(self) -> None:
        """Capture output fragments into the framebuffer."""
        INT_BITS  = self.INT_BITS
        FRAC_BITS = self.FRAC_BITS

        print(self.SCREEN_WIDTH, self.SCREEN_HEIGHT)

        while True:
            await RisingEdge(self.dut.clk)
            if int(self.dut.o_dv.value) == 0:
                continue

            x_val = fp(bin(self.dut.o_fragment_x.value), True, INT_BITS, FRAC_BITS)
            y_val = fp(bin(self.dut.o_fragment_y.value), True, INT_BITS, FRAC_BITS)
            x, y = int(x_val), int(y_val)
            if not (0 <= x < self.SCREEN_WIDTH and 0 <= y < self.SCREEN_HEIGHT):
                continue

            depth = fp(
                bin(self.dut.o_fragment_attr[0].value),
                True, INT_BITS, FRAC_BITS
            ).__float__()

            if not depth < self.depthbuffer[y, x]:
                continue

            rgb = []
            for c in range(3):
                attr_fp = fp(
                    bin(self.dut.o_fragment_attr[c+1].value),
                    True, INT_BITS, FRAC_BITS
                )
                rgb.append(float(attr_fp))
            # rgb = [depth, depth, depth]
            self.framebuffer[y, x, :] = rgb
            self.depthbuffer[y, x] = depth


    def show_framebuffer(self, title: str = "Framebuffer") -> None:
        plt.figure()
        plt.imshow(np.clip(self.framebuffer, 0.0, 1.0))
        plt.title(title)
        # plt.axis("off")
        plt.show()

def color_to_fp_rgb(tb, color):
    r, g, b = color
    INT_BITS  = tb.INT_BITS
    FRAC_BITS = tb.FRAC_BITS
    rng       = tb._OUTPUT_RANGE

    return [LogicArray(fp(r, True, INT_BITS, FRAC_BITS).bits, rng), LogicArray(fp(g, True, INT_BITS, FRAC_BITS).bits, rng), LogicArray(fp(b, True, INT_BITS, FRAC_BITS).bits, rng)]

@cocotb.test()
async def test_triangle(dut: Any) -> None:
    """Test module"""
    SCREEN_WIDTH, SCREEN_HEIGHT = 640, 480
    tb = Testbench(dut, SCREEN_WIDTH, SCREEN_HEIGHT)
    tb.start()
    await tb.reset()

    tb.dut.fb_wr_ready.value = 1
    tb.dut.fb_base.value   = 0x0
    tb.dut.fb_stride.value = 4 * SCREEN_WIDTH

    tb.dut.fb_width.value  = SCREEN_WIDTH
    tb.dut.fb_height.value = SCREEN_HEIGHT
    tb.dut.clear_color.value = 0xFFAABBCC

    v0_color = (1.0, 0.0, 0.0)   # red
    v1_color = (0.0, 1.0, 0.0)   # green
    v2_color = (0.0, 0.0, 1.0)   # blue
    triangle = [[0.5, 0.0, 0.1], [0.0, 1.0, 0.5], [1.0, 1.0, 1.0]]
    for i in range(3):
        triangle[i][0] *= SCREEN_WIDTH
        triangle[i][1] *= SCREEN_HEIGHT
    
    triangle_fp = tb.model.triangle_float_to_fp(triangle)
    v0_attr = color_to_fp_rgb(tb, v0_color)
    v1_attr = color_to_fp_rgb(tb, v1_color)
    v2_attr = color_to_fp_rgb(tb, v2_color)

    tb.dut.v0.value = triangle_fp[0]
    tb.dut.v1.value = triangle_fp[1]
    tb.dut.v2.value = triangle_fp[2]
    tb.dut.v0_attr.value = v0_attr
    tb.dut.v1_attr.value = v1_attr
    tb.dut.v2_attr.value = v2_attr

    print(triangle_fp[0])
    print(triangle_fp[1])
    print(triangle_fp[2])
    print()
    print(v0_attr)
    print(v1_attr)
    print(v2_attr)

    tb.cmd_drv.send({
        "cmd": 0x2
    })

    await RisingEdge(tb.dut.render_done_dbg)
    print(tb.dut.status)

    # tb.dut.i_ready.value       = 1
    # tb.dut.screen_width.value  = SCREEN_WIDTH
    # tb.dut.screen_height.value = SCREEN_HEIGHT
    #
    #
    # cycles = await tb.measure_cycles_for_current_triangle()
    # print(f"Triangle completed in {cycles} clock cycles")
    #   
    # if int(tb.dut.culled_triangle.value) == 1:
    #     print(f"Triangle was culled")
    #
    # await tb.clk_drv.cycles(10)
    # tb.stop()
    #
    # tb.show_framebuffer(f"Rasterized triangle")
