# Lab 1 — Mathematical Expressions

## Overview

This laboratory work focuses on implementing mathematical expressions in **Assembly language** and verifying their correctness by comparing the results with equivalent **C++ implementations**.

The lab consists of **three independent tasks**, each requiring:

* Reading input values from the user
* Computing a mathematical expression
* Outputting the result
* Verifying that the Assembly output matches the C++ reference output

All test cases provided below were executed on both implementations and produced identical results.

---

## Task 1

### Formula

[ Y = (3 + x2 - 7x + 10) / (3 + x2 - 7a + b) + x ]

### Input

* `x`
* `a`
* `b`

### Test Cases

| x | a  | b   | C++ Result | Assembly Result |
| - | -- | --- | ---------- | --------------- |
| 3 | 4  | 5   | 3          | 3               |
| 6 | 7  | 8   | 3          | 3               |
| 5 | 5  | 5   | 4          | 4               |
| 1 | 1  | 1   | -2         | -2              |
| 3 | 33 | 333 | 3          | 3               |

---

## Task 2

### Formula

[
Y = (1 + Sin(x + y) * Sin(x + y)) / (2 + fabs(x - 2 * x / (1 + x * x * y * y))) + x
]

### Input

* `x`
* `y`

### Test Cases

| x  | y  | C++ Result | Assembly Result |
| -- | -- | ---------- | --------------- |
| 1  | 1  | 1          | 1               |
| 44 | 44 | 44         | 44              |
| 3  | 7  | 3          | 3               |
| 8  | 7  | 8          | 8               |
| -4 | 3  | -3         | -3              |

---

## Task 3

### Formula

[ Y = tg(x * x / 4 + x / 2 + 1) ]

### Input

* `x`

### Test Cases

| x  | C++ Result | Assembly Result |
| -- | ---------- | --------------- |
| 6  | 0.470781   | 0.470781        |
| 3  | 1.15784    | 1.15784         |
| -8 | 0.470781   | 0.470781        |

---

## Notes

* Floating-point calculations are performed using the FPU in Assembly.
* All results from the Assembly implementation fully match the reference C++ outputs.
* Input and output formats are consistent across both implementations for easy comparison.

---

## Conclusion

This lab demonstrates correct usage of arithmetic operations, trigonometric functions, and floating-point math in Assembly language, as well as validation against a high-level language implementation.
