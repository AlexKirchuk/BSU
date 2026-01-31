# Lab 9: Classes, Operator Overloading, Exceptions

## Task Description

### Task 1

Develop a **dynamic array class** for sorting array elements.

The class must include:

* a default constructor
* a copy constructor
* a destructor

Additional requirements:

* Input/output operations: overload `<<` and `>>` as **friend functions**
* Overload all additional necessary operators
* Implement **exception handling**

---

### Task 2

Implement a **class for solving Task #2**, inventing your own problem.

The class must include:

* a constructor
* a copy constructor
* a destructor

Additional requirements:

* Overload necessary **arithmetic and logical operators** as class members:
  `+`, `-`, `*`, `/`, `++`, `--`, `=`, `==`, `!=`, `>=`, `<=`
* Overload operations and implement functions for working with multiple objects using `+`, `-`, `*`
* Input/output operations: overload `<<` and `>>` as **friend functions**
* Implement **exception handling**
* Overload all additional necessary functions

---

## Invented Problem 1 — Deposit Profit Calculation

If one dollar is deposited at **100% annual interest**, the result after one year will be **2 dollars**.

However, if the money is deposited at **100% for 6 months**, withdrawn, and then deposited again at **100%**, the final amount will be **2.25 dollars**.

The task is to determine:

* What profit will be obtained if interest is calculated **daily**?
* What profit will be obtained if interest is calculated **hourly**?
* What value does the profit tend to as the compounding period decreases?

---

## Invented Problem 2 — Choosing the Best Bank

There are three banks offering different interest rates with maximum limits:

* **Bank 1**: 5% interest, maximum deposit — 70
* **Bank 2**: 7% interest, maximum deposit — 60
* **Bank 3**: 9% interest, maximum deposit — 50

The task is to determine **which bank provides the best option for depositing money** under these conditions.

---

## Program Features

* Implementation of custom classes with dynamic memory management
* Operator overloading (arithmetic, logical, assignment, input/output)
* Sorting using **Shell sort**
* Exception handling for invalid input values
* Demonstration of object-oriented programming principles in C++
