import os
import sys
from pathlib import Path

import pytest
from cocotb_tools.runner import get_runner

# Redefine this when copying testbench runner to another module
MODULE_TOP_LEVEL_NAME = "rasterizer_core"
MODULE_FILE_PATH      = "../src/rasterizer_core.sv"
MODULE_DEPENDENCIES   = [
    "../src/fast_inverse_q.sv",
    "../src/rasterizer_frontend.sv",
    "../src/rasterizer_backend_quad.sv"
]

def test_module():
    # Env variables
    hdl_toplevel_lang = os.getenv("HDL_TOPLEVEL_LANG", "verilog") # for verilator only verilog is supported (this includes systemverilog)
    sim = os.getenv("SIM", "verilator")

    # Project files
    proj_path = Path(__file__).resolve().parent
    repo_root = proj_path.parents[2] # This only holds for a modules/MODULE_NAME/tb path

    sources   = [proj_path / MODULE_FILE_PATH, *[proj_path / path for path in MODULE_DEPENDENCIES]]

    # Define runner
    sys.path.append(str(proj_path / "tests"))
    runner = get_runner(sim)

    build_args = []
    parameters = {
        "SIGNED": "1",
        "INT_BITS": "16",
        "FRAC_BITS": "16",
        "AREA_FRAC_BITS": "12",
        "SCREEN_WIDTH":  "1280",
        "SCREEN_HEIGHT": "720",
    }

    runner.build(
        hdl_toplevel=MODULE_TOP_LEVEL_NAME,
        sources=sources,
        build_args=build_args,
        parameters=parameters,
        always=True,
        waves=True
    )

    runner.test(
        hdl_toplevel=MODULE_TOP_LEVEL_NAME,
        hdl_toplevel_lang=hdl_toplevel_lang,
        test_module="rasterizer_tests",
        waves=True
    )

if __name__ == "__main__":
    test_module()

