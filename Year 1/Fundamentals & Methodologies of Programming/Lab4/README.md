# Lab 4: Array and Sequence Processing

## Description

This laboratory work consists of **four independent tasks** related to processing sequences and arrays. All tasks are implemented in **one C++ program**, structured using separate functions. The original algorithm logic is preserved.

---

## Task 1. Arithmetic and Geometric Progression

### Problem Statement

Given an integer sequence:

A = (a1, a2, ..., an), where 1 ≤ n ≤ 100.

Determine whether the sequence forms:

* an **arithmetic progression**, or
* a **geometric progression**.

If the sequence is arithmetic, output the common difference **d**.
If the sequence is geometric, output the common ratio **q**.
If the sequence is neither, output a corresponding message.

### Algorithm Idea

1. Compute the initial difference d = a2 − a1 and the ratio q = a2 / a1.
2. Traverse the sequence and compare each consecutive difference or ratio.
3. If all values match, the sequence is a progression.
4. Special cases are handled for sequences of length 1 or 2.

---

## Task 2. Reordering by Even Digit Sum

### Problem Statement

Transform an integer sequence:

A = (a1, a2, ..., an), where n ≤ 100,

by placing first all numbers whose **sum of digits is even**, and then all remaining numbers, **while preserving their relative order**.

### Algorithm Idea

1. Use a modified bubble-sort-like algorithm.
2. For each element, compute the sum of its digits.
3. If the current element has an even digit sum and the previous one does not, swap them.
4. Repeat the process n times to ensure correct ordering.

---

## Task 3. Intersection of Two Non-Decreasing Arrays

### Problem Statement

Given two non-decreasing arrays:

X = (x1, x2, ..., xn), where n ≤ 10,
Y = (y1, y2, ..., ym), where m ≤ 10.

Find their **intersection** — an array Z that contains all common elements.
The multiplicity of each element in Z is equal to the minimum of its multiplicities in X and Y.

The algorithm must work in O(n + m) time.

### Algorithm Idea

1. Traverse both arrays simultaneously using two indices.
2. Compare the current elements:

    * If one is smaller, advance the corresponding index.
    * If they are equal, count repetitions in both arrays.
3. Add the element to array Z the minimum number of times found.

---

## Task 4. Counting Distinct Elements

### Problem Statement

Given an integer sequence:

A = (a1, a2, ..., an), where n ≤ 100.

Determine the **number of distinct elements** in the sequence.
The algorithm complexity must be O(n²).

### Algorithm Idea

1. Sort the array using bubble sort.
2. Traverse the sorted array and compare neighboring elements.
3. Increase a counter whenever the current element differs from the previous one.

---

## Notes

* All tasks are implemented in a single program using separate functions.
* The program supports both manual and random input where required.
* Input constraints are validated to prevent incorrect data entry.
