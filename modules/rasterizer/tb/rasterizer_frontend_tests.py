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
        """Send data to the output and evaluate the model."""
        triangle_list = [i_v0, i_v1, i_v2]
        self.log.debug("Received input:\n  triangles: %r", triangle_list)

        # Turn fixed point into float
        triangle_list_float = self.triangle_fp_to_float(triangle_list)

        # Compute expected output
        v1, v2, v3 = triangle_list_float
        print(v1, v2, v3)

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
        if (area <= 0):
            should_be_culled = 1
        print(f"Should be culled: {should_be_culled}")

        # Compute barycentric weights at top-left corner of bounding box
        area_reciprocal = 1 / area
        print("area:     ", area, bin(fp(area, True, 24, 8).bits))
        print("area inv: ", area_reciprocal, bin(fp(area_reciprocal, True, 4, 28).bits))

        w1 = e1 * area_reciprocal
        w2 = e2 * area_reciprocal
        w3 = e3 * area_reciprocal

        # Compute increments for barycentric weights
        w1_dx = e1_dx * area_reciprocal
        w1_dy = e1_dy * area_reciprocal

        w2_dx = e2_dx * area_reciprocal
        w2_dy = e2_dy * area_reciprocal

        w3_dx = e3_dx * area_reciprocal
        w3_dy = e3_dy * area_reciprocal

        # Initialize z at the top-left corner
        z = (w1 * v1[2]) + (w2 * v2[2]) + (w3 * v3[2])

        # Compute z increments
        z_dx = (w1_dx * v1[2]) + (w2_dx * v2[2]) + (w3_dx * v3[2])
        z_dy = (w1_dy * v1[2]) + (w2_dy * v2[2]) + (w3_dy * v3[2])

        # Turn back into fixed point
        result_fixed = [
            [
                self.float_to_fp(min_x, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
                self.float_to_fp(min_y, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
            ],
            [
                self.float_to_fp(max_x, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
                self.float_to_fp(max_y, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
            ],

            self.float_to_fp(e1, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
            self.float_to_fp(e2, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
            self.float_to_fp(e3, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
            
            [
                self.float_to_fp(e1_dx, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
                self.float_to_fp(e1_dy, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
            ],
            [
                self.float_to_fp(e2_dx, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
                self.float_to_fp(e2_dy, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
            ],
            [
                self.float_to_fp(e3_dx, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
                self.float_to_fp(e3_dy, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
            ],

            [
                self.float_to_fp(z, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
                0.0, 0.0, 0.0, # RGB colors not used
            ],
            [
                self.float_to_fp(z_dx, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
                0.0, 0.0, 0.0,
            ],
            [
                self.float_to_fp(z_dy, True, self.INT_BITS, self.FRAC_BITS, self._OUTPUT_RANGE),
                0.0, 0.0, 0.0,
            ]
        ]

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

        self.clk_drv = Clock(self.dut.clk, 10, unit="ns")

        self.input_drv = DataValidDriver(
            name=f"{self.name}.input_drv",
            clk=self.dut.clk,
            rstn=self.dut.rstn,
            valid=self.dut.i_dv,
            datas={
                "i_v0": self.dut.i_v0,
                "i_v1": self.dut.i_v1,
                "i_v2": self.dut.i_v2
            },
            initial_values={
                "i_v0": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
                "i_v1": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)],
                "i_v2": [LogicArray(0, self._OUTPUT_RANGE) for _ in range(3)]
            }
        )
        
        self.input_monitor = DataValidMonitor(
            name=f"{self.name}.input_monitor",
            clk=self.dut.clk,
            rstn=self.dut.rstn,
            valid=self.dut.i_dv,
            datas={
                "i_v0": self.dut.i_v0, 
                "i_v1": self.dut.i_v1, 
                "i_v2": self.dut.i_v2, 
            },
        )
        
        self.output_monitor = DataValidMonitor(
            name=f"{self.name}.output_monitor",
            clk=self.dut.clk,
            rstn=self.dut.rstn,
            valid=self.dut.o_dv,
            datas={
                "o_bb_tl": self.dut.o_bb_tl,
                "o_bb_br": self.dut.o_bb_br,

                "o_edge_val0": self.dut.o_edge_val0,
                "o_edge_val1": self.dut.o_edge_val1,
                "o_edge_val2": self.dut.o_edge_val2,

                "o_edge_delta0": self.dut.o_edge_delta0,
                "o_edge_delta1": self.dut.o_edge_delta1,
                "o_edge_delta2": self.dut.o_edge_delta2,

                "o_attr0": self.dut.o_attr0,
                "o_attr_dx": self.dut.o_attr_dx,
                "o_attr_dy": self.dut.o_attr_dy,
            }
        )
        
        self.model = RasterizerFrontendModel(
            name=f"{self.name}.model",
            FRAC_BITS=self.FRAC_BITS,
            INT_BITS=self.INT_BITS,
            SCREEN_WIDTH=self.SCREEN_WIDTH,
            SCREEN_HEIGHT=self.SCREEN_HEIGHT
        )

        def compare_output(expected, actual) -> bool:
            output_names = [
                "o_bb_tl", 
                "o_bb_br",
                "o_edge_val0",
                "o_edge_val1",
                "o_edge_val2",
                "o_edge_delta0",
                "o_edge_delta1",
                "o_edge_delta2",
                "o_attr0",
                "o_attr_dx",
                "o_attr_dy",
            ]

            printing = True
            correct  = True
            for i in range(len(expected)):
                if type(expected[i]) != LogicArray:
                    if (printing):
                        print("\n------------------------------------------------------\n")
                        print(f"{output_names[i]}:")

                    for j in range(len(expected[i])):
                        if printing:
                            print(expected[i][j], " <- Expected")
                            print(actual[i][j],   " <- Got")
                            if j != len(expected[i]) - 1:
                                print()

                        if expected[i][j] != actual[i][j]:
                            correct = False
                else:
                    if printing:
                        print("\n------------------------------------------------------\n")
                        print(f"{output_names[i]}:")
                        print("Expected:")
                        print(expected[i])
                        print("Got:")
                        print(actual[i])

                    if expected[i][j] != actual[i][j]:
                        correct = False

            return True

        self.checker = InOrderChecker[Sequence[List[LogicArray]]](
            name=f"{self.name}.checker",
            cmp=compare_output
        )

        # connect monitors to model and checker
        self.input_monitor.add_callback(
            lambda datas: self.model.send_input(
                i_v0=datas["i_v0"],
                i_v1=datas["i_v1"],
                i_v2=datas["i_v2"],
            )
        )
        self.model.add_output_callback(self.checker.addExpected)
        self.output_monitor.add_callback(
            lambda datas: self.checker.addActual([
                datas["o_bb_tl"],
                datas["o_bb_br"],
                datas["o_edge_val0"],
                datas["o_edge_val1"],
                datas["o_edge_val2"],
                datas["o_edge_delta0"],
                datas["o_edge_delta1"],
                datas["o_edge_delta2"],

                datas["o_attr0"],
                datas["o_attr_dx"],
                datas["o_attr_dy"],
            ])
        )

    def start(self) -> None:
        self.clk_drv.start()
        self.input_drv.start()
        self.input_monitor.start()
        self.output_monitor.start()

    def stop(self) -> None:
        self.clk_drv.stop()
        self.input_drv.stop()
        self.input_monitor.stop()
        self.output_monitor.stop()

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

    # Apply ready on output port of frontend
    tb.dut.i_ready.value = 1

    triangle = [[0.5, 0.0, 0.1], [0.0, 1.0, 0.5], [1.0, 1.0, 1.0]]
    for i in range(3):
        triangle[i][0] *= tb.SCREEN_HEIGHT
        triangle[i][1] *= tb.SCREEN_HEIGHT

    triangle_fp = tb.model.triangle_float_to_fp(triangle)
    tb.input_drv.send({
        "i_v0": triangle_fp[0],
        "i_v1": triangle_fp[1],
        "i_v2": triangle_fp[2],
    })
    
    await First(
        RisingEdge(tb.dut.culled_triangle),
        RisingEdge(tb.dut.o_dv)
    )
    if (tb.dut.culled_triangle.value == 1):
        print("This triangle was invalid and therefore culled")

    await tb.clk_drv.cycles(5)
    tb.stop()
