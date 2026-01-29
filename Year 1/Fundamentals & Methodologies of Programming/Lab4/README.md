# Lab 4: Array and Sequence Processing

## Description

This laboratory work consists of **four independent tasks** related to processing integer and real-number sequences and arrays. All tasks are implemented in **one C++ program** with a single `main()` function and a clear functional structure. The logic of the original algorithms is preserved.

---

## Task 1: Arithmetic and Geometric Progression

### Problem Statement

Given an integer sequence ( A = (a_i) ), ( i = 1..n ), where ( n \le 100 ), determine whether the sequence forms:

* an **arithmetic progression**;
* a **geometric progression**.

If the sequence is an arithmetic progression, output the common difference ( d ).
If the sequence is a geometric progression, output the common ratio ( q ).
If the sequence is neither, output a corresponding message.

### Algorithm Idea

1. Compute the difference ( d = a_2 - a_1 ) or ratio ( q = a_2 / a_1 ).
2. Traverse the sequence and compare all consecutive differences or ratios.
3. If all values are equal, the sequence is a progression.
4. Special cases are handled separately for sequences of length 1 or 2.

### Test Examples

```
Input:  { -5, -3, -1, 1, 3 }
Output: Arithmetic progression, d = 2

Input:  { 1, 3, 9, 27, 81 }
Output: Geometric progression, q = 3

Input:  { 3, 3, 3, 3, 3 }
Output: Stationary sequence
```

---

## Task 2: Reordering by Even Digit Sum

### Problem Statement

Transform an integer sequence ( A = (a_i) ), ( i = 1..n ), ( n \le 100 ), by placing:

1. First — all numbers whose **sum of digits is even**;
2. Then — all remaining numbers.

The **original order inside each group must be preserved**.

### Algorithm Idea

1. Use a modified bubble-sort–like approach.
2. For each element, compute the sum of its digits.
3. If the current element has an even digit sum and the previous one does not, swap them.
4. Repeat the process until the array is reordered.

### Test Example

```
Input:  6 74 56 21 91 12 29 48 91 9
Output: 6 91 48 91 74 56 21 12 29 9
```

---

## Task 3: Intersection of Two Non-Decreasing Arrays

### Problem Statement

Given two non-decreasing arrays:

* ( X = (x_i) ), ( i = 1..n ), ( n \le 10 );
* ( Y = (y_i) ), ( i = 1..m ), ( m \le 10 ).

Find their **intersection** — an array ( Z ) that contains all common elements. The multiplicity of each element in ( Z ) must be equal to the **minimum multiplicity** of that element in ( X ) and ( Y ).

The algorithm must work in ( O(n + m) ) time.

### Algorithm Idea

1. Traverse both arrays simultaneously using two indices.
2. If elements are equal, count their occurrences in both arrays.
3. Add the element to the result array the minimum number of times.
4. Move the indices forward accordingly.

### Test Example

```
X: 1 1 1 2 6 6 8
Y: 1 1 3 4 6 6 6 6 9
Result: 1 1 6 6
```

---

## Task 4: Counting Distinct Elements

### Problem Statement

Given an integer sequence ( A = (a_i) ), ( i = 1..n ), ( n \le 100 ), determine the **number of distinct elements** in the array.

The number of operations must be of order ( O(n^2) ).

### Algorithm Idea

1. Sort the array using bubble sort.
2. Traverse the sorted array.
3. If the current element differs from the next one, increase the counter.
4. The final counter value equals the number of distinct elements.

### Test Example

```
Input:  22 39 23 50 21 37 37 62 60 57
Output: Number of distinct elements = 9
```

---

## Notes

* All tasks are implemented in a single program using separate functions.
* Input validation is performed according to the given constraints.
* The program is intended for educational purposes and focuses on algorithmic correctness rather than optimization.
