# Lab 2 — Assembly Language Calculator

## Overview

This laboratory work implements a **simple calculator** using **C++** and **inline Assembly**.
The goal of the lab is to demonstrate conditional logic, arithmetic operations, and correct branching in Assembly language, while verifying results against a C++ reference implementation.

The calculator supports the four basic arithmetic operations:

* Addition (`+`)
* Subtraction (`-`)
* Multiplication (`*`)
* Division (`/`)

All computations are performed on integer values.

---

## Task Description

### Input

The program sequentially reads:

* Integer value `x`
* Integer value `y`
* Arithmetic operation (`+`, `-`, `*`, `/`)

### Output

* Result calculated using **C++**
* Result calculated using **Assembly language**

Both results must be identical.

---

## Supported Operations

| Operation | Description      |
| --------- | ---------------- |
| `+`       | Addition         |
| `-`       | Subtraction      |
| `*`       | Multiplication   |
| `/`       | Integer division |

---

## Test Cases

| x | y  | Operation | C++ Result | Assembly Result |
| - | -- | --------- | ---------- | --------------- |
| 3 | 4  | `+`       | 7          | 7               |
| 4 | 6  | `-`       | -2         | -2              |
| 4 | -3 | `*`       | -12        | -12             |
| 9 | -3 | `/`       | -3         | -3              |

---

## Notes

* Division is performed as **integer division**.
* Assembly implementation uses conditional branching to select the correct operation.
* Input validation is assumed to be correct (division by zero is not tested).
* The program is intended for **x86 architecture** using MSVC-style inline Assembly.

---

## Conclusion

This laboratory work demonstrates how basic arithmetic operations and control flow can be implemented in Assembly language and validated against a high-level C++ solution. The results confirm the correctness of the Assembly implementation for all supported operations.
