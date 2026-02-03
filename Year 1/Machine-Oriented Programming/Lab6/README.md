# Lab 6 — Matrix Row Analysis

## Task Description

Given a matrix **A = (aᵢⱼ)** of size **n × m**, where:

* **i = 1..n**, **j = 1..m**
* **n, m ≤ 150**

It is required to:

* Find the **maximum number of positive elements** among all rows of the matrix
* Determine the **indices of the rows** that contain this maximum number of positive elements

The task must be implemented in **both C++ and Assembly language**, and the results must match.

---

## Input

* Integers **n** and **m** — number of rows and columns
* Matrix **A** consisting of integer elements

---

## Output

The program outputs:

1. The maximum number of positive elements in a row
2. The indices (1-based) of the rows where this maximum is achieved

Output format (for both C++ and Assembly):

* `The maximum number of positive elements is X`
* `Row indices with the maximum number of positive elements: ...`

---

## Test Cases

### Test 1

**Input matrix:**

```
 0   1
 0  -1
 1  -1
```

**Output:**

```
The maximum number of positive elements is 1
Row indices with the maximum number of positive elements: 1 3
```

---

### Test 2

**Input matrix:**

```
 0   1   0
-1   1  -1
-1  -1   0
-2  -1  -2
```

**Output:**

```
The maximum number of positive elements is 1
Row indices with the maximum number of positive elements: 1 2
```

---

### Test 3

**Input matrix:**

```
 0   1   0  -1   1  -1  -1  -1
 0  -2  -1  -2   0  -1  -1  -1
-1  -1  -1  -2  -2   1   1   0
-1   1  -1  -2  -1   0   0   0
-2   1   1  -1   1  -1  -2   1
-1   0   1   1  -1  -2  -2   1
 0   0  -1  -2   1  -1  -2  -1
-1  -2   1  -2   0  -2  -2   0
```

**Output:**

```
The maximum number of positive elements is 4
Row indices with the maximum number of positive elements: 5
```

---

## Notes

* Row numbering starts from **1**
* Zero is **not** considered a positive number
* The Assembly implementation uses processor instructions to iterate over the matrix and count positive elements
* The algorithm complexity is **O(n × m)**

---

## Conclusion

This laboratory work demonstrates matrix processing using both **high-level (C++)** and **low-level (Assembly)** approaches, ensuring identical logic and output across implementations.
