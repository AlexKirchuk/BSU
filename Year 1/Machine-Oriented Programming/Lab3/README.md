# Lab 3 — Kaprekar Numbers

## Overview

This laboratory work implements a program to determine whether a given number is a **Kaprekar number**.
The task is solved using both **C++** and **Assembly language**, with explicit usage of **CPU instructions** in the Assembly implementation.

The goal of the lab is to practice working with arithmetic operations, integer manipulation, and control flow at a low level, while validating the Assembly solution against a C++ reference.

---

## Task Description

### Problem Statement

A **Kaprekar number** (in a given numeral system) is a non-negative integer whose **square** can be split into two parts such that the **sum of those parts equals the original number**.

For example:

* (45^2 = 2025)
* Split: `20` and `25`
* (20 + 25 = 45)

Therefore, **45 is a Kaprekar number**.

Kaprekar numbers are named after **D. R. Kaprekar**.

---

## Input

* A non-negative integer value `A`

## Output

* A message stating whether the number **is** or **is not** a Kaprekar number

The result is printed twice:

* Using a **C++ implementation**
* Using an **Assembly language implementation**

Both outputs must match.

---

## Test Results

### C++ Output

The following numbers were tested and identified as Kaprekar numbers:

* 1
* 9
* 45
* 55
* 99
* 297
* 703
* 999

### Assembly Output

The Assembly implementation produced **identical results**:

* 1
* 9
* 45
* 55
* 99
* 297
* 703
* 999

---

## Notes

* The program works with **integer arithmetic**.
* The Assembly version explicitly uses **processor instructions** for multiplication, division, and comparison.
* The solution follows the requirements of the lab by implementing at least one task from the first-semester assignment in both C++ and Assembly.
* The program is intended for **x86 architecture** with MSVC-style inline Assembly.

---

## Conclusion

This laboratory work demonstrates how a non-trivial numerical property can be checked using low-level Assembly instructions and validated against a high-level C++ solution. The identical results confirm the correctness of the Assembly implementation.
