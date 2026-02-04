# Machine-Oriented Programming — Lab Work Collection

This directory contains a complete collection of laboratory works for the course **Machine-Oriented Programming**.

All laboratory works are implemented in **C++17** with extensive use of **x86 Assembly language**, demonstrating low-level programming concepts, interaction between C++ and Assembly, and direct usage of processor instructions.

The projects were developed and tested using **Microsoft Visual Studio 2026**, built with **CMake**, and targeted for **x86 (32-bit)** architecture where required.

---

## Overview

* Total of **8 laboratory works** included in this repository.
* Each lab focuses on a specific aspect of **machine-oriented and low-level programming**.
* Most laboratory works combine **C++** and **inline Assembly** (`__asm`), except **Lab 8**, which uses **separate Assembly (.asm) files**.
* The collection demonstrates arithmetic operations, sequence and array processing, binary operations, matrix analysis, string processing, and Assembly–C++ integration.

---

## Laboratory Works

1. **Lab 1 — Mathematical Expressions**
   Evaluation of mathematical expressions using both C++ and Assembly language, with result comparison.

2. **Lab 2 — Assembly Language Calculator**
   Implementation of a basic calculator supporting arithmetic operations using C++ and Assembly.

3. **Lab 3 — Kaprekar Numbers**
   Determination of whether a number is a Kaprekar number using C++ and Assembly logic.

4. **Lab 4 — Array and Sequence Processing**
   Analysis of integer sequences (arithmetic and geometric progressions) and array intersection problems.

5. **Lab 5 — Binary Number Operations**
   Binary representation processing, zero removal, bit reversal, palindrome checking, and power-of-two computation.

6. **Lab 6 — Matrix Row Analysis**
   Finding rows of a matrix containing the maximum number of positive elements using C++ and Assembly.

7. **Lab 7 — String Processing**
   Single-pass string analysis to find words with the maximum number of distinct characters.

8. **Lab 8 — Assembly Functions Integration**
   Integration of external Assembly functions (`.asm`) with C++ using `extern "C"` and CMake.

---

## Notes

* Inline Assembly (`__asm`) is used in most labs and is supported only in **32-bit MSVC builds**.
* Lab 8 demonstrates a different approach by placing Assembly code in a separate `.asm` file.
* All projects are structured for educational purposes and closely follow the requirements of the course.

---

This directory serves as a structured and practical reference for studying **machine-oriented programming**, combining **high-level C++** with **low-level Assembly language techniques**.
