from cocotb.types import LogicArray, Range
from fixedpoint import FixedPoint as fp


A = fp("0xFFFFFF", False, 0, 24)
B = fp("0xABABAB", False, 0, 24)
C = "0x" + str(A) + str(B)
C_fp = fp(C, False, 48, 0)
print(str(A), str(B), C, C_fp, int(C_fp))

r = Range(47, "downto", 0)
A = LogicArray(int(C_fp), r)
print(A)
