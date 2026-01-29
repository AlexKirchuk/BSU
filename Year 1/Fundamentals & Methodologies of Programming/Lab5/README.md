# Lab 5: Matrix Processing and Smoothing

## Description

This laboratory work consists of **two independent tasks** related to matrix operations. Both tasks are implemented in **one C++ program**, structured using separate functions. The original algorithm logic is preserved.

---

## Task 1. Rows with Maximum Positive Elements

### Problem Statement

Given an integer matrix:

A = (aᵢⱼ), where 1 ≤ i ≤ n, 1 ≤ j ≤ m, n, m ≤ 150.

Determine the **row(s) containing the maximum number of positive elements**.
If all elements are non-positive, display an appropriate message.

### Algorithm Idea

1. Traverse each row of the matrix and count the number of positive elements.
2. Keep track of the maximum count found so far.
3. After counting all rows, compare each row’s positive count with the maximum.
4. Output the row indices where the number of positive elements equals the maximum.

---

## Task 2. Matrix Smoothing

### Problem Statement

Given a real matrix:

A = (aᵢⱼ), where 1 ≤ i ≤ n, 1 ≤ j ≤ m, n, m ≤ 100.

Perform a **smoothing operation**:

* Each element in the resulting matrix is the arithmetic mean of its neighbors.
* Neighbors of aᵢⱼ are elements aₖg where i−1 ≤ k ≤ i+1, j−1 ≤ g ≤ j+1, and (k, g) ≠ (i, j).
* Elements outside the matrix bounds are ignored.

### Algorithm Idea

1. Traverse the original matrix element by element.
2. For each element, iterate over all potential neighbors using nested loops.
3. Check if a neighbor is within bounds and not the element itself.
4. Accumulate the sum and count of neighbors.
5. Compute the average and assign it to the corresponding element in the resulting matrix.

---

## Notes

* Both tasks are implemented in a single program using separate functions.
* Random matrix initialization is used for demonstration; manual input can be added.
* Matrix dimensions are validated to prevent incorrect data entry.
* The program uses dynamic memory allocation for the smoothing task; proper memory management should be applied when extending.
