# Lab 5 — Binary Number Operations

## Overview

This laboratory work focuses on **bit-level operations** and number manipulation in the **binary numeral system**.
All tasks are implemented using **C++** and **Assembly language**, with explicit usage of processor instructions for bitwise operations, shifts, and arithmetic.

The lab consists of several independent subtasks related to binary representation of integers.

---

## Task Description

Given an integer number, perform the following operations:

### Part A — Binary Transformations

1. Convert the input number to **binary representation (base 2)**.
2. Remove all `0` bits from the binary representation.
3. Reverse the resulting binary number.

### Part B — Additional Operations

1. Determine whether the resulting binary number is a **palindrome**.
2. Compute the value of **(2^n)** for a given exponent `n`.

---

## Input

* An integer number
* An integer exponent `n`

## Output

The program outputs:

* Binary representation of the input number
* Binary number with all `0` bits removed
* Reversed binary number
* Result of the palindrome check
* Value of (2^n)

All results are displayed for both **C++** and **Assembly** implementations.

---

## Test Results

### Test Case 1

```
Enter number: 123
Binary representation: 0000000001111011
Binary without zeros: 0000000000111111
Reversed binary: 0000000001101111
Is not a palindrome
Enter power: 3
2^n = 8
```

---

### Test Case 2

```
Enter number: 21
Binary representation: 0000000000010101
Binary without zeros: 0000000000000111
Reversed binary: 0000000000010101
Is a palindrome
Enter power: 1
2^n = 2
```

---

### Test Case 3

```
Enter number: 444
Binary representation: 0000000110111100
Binary without zeros: 0000000000111111
Reversed binary: 0000000001111011
Is not a palindrome
Enter power: 4
2^n = 16
```

---

## Notes

* All binary values are displayed using a **fixed-length representation**.
* Zero removal and reversal are implemented using **bitwise operations**.
* Palindrome checking is performed by comparing the binary sequence with its reverse.
* The power function (2^n) is calculated using bit shifting in Assembly.
* The program is designed for **x86 architecture** with MSVC-style inline Assembly.

---

## Conclusion

This laboratory work demonstrates practical usage of binary arithmetic, bit manipulation, and control flow in Assembly language. The identical results from C++ and Assembly implementations confirm the correctness of low-level bitwise processing.
