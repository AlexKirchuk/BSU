# Lab 8 — Assembly Functions Integration

## Task

This laboratory work demonstrates the use of **separate Assembly (.asm) files** integrated with a **C++ program** using external functions.

All assembly routines are implemented in a separate file:

```
functions.asm
```

The C++ code accesses them using declarations of the form:

```cpp
extern "C" int functionName(...);
```

---

## Implemented Tasks

1. **Sum of two numbers**
   Calculate the sum of two integers.

2. **Kaprekar number check**
   Determine whether a given number is a Kaprekar number.

3. **Arithmetic / Geometric progression check**
   Determine whether a sequence of integers forms an arithmetic or geometric progression.

4. **Remove zeros from a number in binary system**
   Convert a number to binary form and remove all zero bits.

5. **Raise 2 to the nth power**
   Compute the value of (2^n).

All calculations for these tasks are performed using **assembly language functions**, which are called from C++.

---

## Input / Output Format

The program sequentially executes all five tasks. Each task requests input data from the user and outputs the result.

---

## Test Example

```
Tasks:
1. Sum of two numbers.
2. Is a Kaprekar number?
3. Is ar/geom progression?
4. Remove zeros from a number in binary system.
5. Raise 2 to the nth power.
--------------------------------------------------------------------------------
1. Enter two numbers:
52
48
Sum: 100
================================================================================
2. Enter number:
45
Kaprekar number?: YES
================================================================================
3. Enter sequence size:
4
Enter elements:
3
9
27
81
Is arithmetic?: NO
Is geometric?: YES
================================================================================
4. Enter number:
43
Entered number in binary system: 0000000000101011
Entered number without zeros in binary system: 0000000000001111
================================================================================
5. Enter power:
6
2^6 = 64
================================================================================
```

---

## Notes

* Assembly code is written in **MASM syntax** and compiled separately.
* Function names and calling conventions are matched using `extern "C"` in C++ and `.model flat, c` in Assembly.
* The project is intended to be built in **x86 mode** (32-bit), as required for MASM stack-based parameter passing.
