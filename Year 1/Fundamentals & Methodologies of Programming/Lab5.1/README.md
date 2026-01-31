# Lab 5.1 — Shell Sort Implementation

## Description

This laboratory work demonstrates the **Shell Sort** algorithm on an integer sequence. The program sorts the sequence in ascending order using a gap-based insertion method.

---

## Problem Statement

Given an integer sequence:
A = (a₁, a₂, ..., aₙ), where n ≤ 100.

Sort the sequence in **ascending order** using **Shell Sort**.

---

## Algorithm Idea

1. Start with a gap `i` greater than 1 (commonly n/2).
2. Compare and sort elements that are `i` positions apart.
3. Reduce the gap and repeat the process until `i = 1`.
4. Perform a standard insertion sort in the final pass (`i = 1`).

Shell Sort improves insertion sort by allowing exchanges of far-apart elements, reducing the total number of shifts.

---

## Test Cases

### Test 1

**Input:**

```
98  51   7  54  12  61  27  63  42  71
```

**Output:**

```
 7  12  27  42  51  54  61  63  71  98
```

### Test 2

**Input:**

```
9  80  97   7  27
```

**Output:**

```
7   9  27  80  97
```

### Test 3

**Input:**

```
54  79  22  15  88  91   5
```

**Output:**

```
5  15  22  54  79  88  91
```

---

## Notes

* The program supports sequences of up to 100 integers.
* Shell Sort provides a compromise between simple insertion sort and more advanced algorithms, achieving better performance on medium-sized arrays.
