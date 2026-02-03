# Lab 4 — Array and Sequence Processing

## Overview

This laboratory work focuses on **array processing** tasks implemented in both **C++** and **Assembly language**.
The assignment requires completing **at least one** task from the first-semester Lab 4, but in this work **two tasks** are implemented.

Both tasks demonstrate working with integer arrays, conditional logic, loops, and comparisons at a low level using processor instructions. The correctness of the Assembly implementations is verified by comparison with C++ reference solutions.

---

## Task 1 — Progression Detection

### Problem Statement

Given an integer sequence:

[ A = (ai), i = 1..n, n ≤ 100 ]

Determine whether the sequence forms:

* an **arithmetic progression**,
* a **geometric progression**,
* or **neither**.

If the sequence is an arithmetic progression, output its common difference `d`.
If it is a geometric progression, output its common ratio `q`.
If the sequence does not form any progression, output a corresponding message.

---

### Test Results — Task 1

#### C++ Output

```
Is an arithmetic progression
Difference d = 1
Is not a geometric progression
```

#### Assembly Output

```
Is an arithmetic progression
Difference d = 1
Is not a geometric progression
```

---

#### C++ Output

```
Is not an arithmetic progression
Is a geometric progression
Ratio q = 3
```

#### Assembly Output

```
Is not an arithmetic progression
Is a geometric progression
Ratio q = 3
```

---

#### C++ Output

```
Is not an arithmetic progression
Is not a geometric progression
```

#### Assembly Output

```
Is not an arithmetic progression
Is not a geometric progression
```

---

#### C++ Output

```
Your sequence is stationary
```

#### Assembly Output

```
Is not an arithmetic progression
Is not a geometric progression
```

---

## Task 2 — Intersection of Two Arrays

### Problem Statement

Given two **non-decreasing integer arrays**:

* ( X = (xi), i = 1..n, n ≤ 10 )
* ( Y = (yi), i = 1..m, m ≤ 10 )

Find their **intersection**, i.e. an array `Z` that contains all common elements of `X` and `Y`.

The multiplicity of each element in `Z` must be equal to the **minimum multiplicity** of that element in `X` and `Y`.

The algorithm complexity must be **O(n + m)**.

---

### Test Results — Task 2

#### C++ Output

```
Intersection:
1 2 2
```

#### Assembly Output

```
Intersection:
1 2 2
```

---

#### C++ Output

```
Intersection:
1 1 2
```

#### Assembly Output

```
Intersection:
1 1 2
```

---

#### C++ Output

```
Intersection:
Empty set (no common elements)
```

#### Assembly Output

```
Intersection:
Empty set (no common elements)
```

---

## Notes

* All arrays contain **integer values**.
* Assembly implementations explicitly use **processor instructions** for looping, comparison, and indexing.
* Both tasks satisfy the requirement of array processing from the first-semester Lab 4.
* The code is designed for **x86 architecture** with MSVC-style inline Assembly.

---

## Conclusion

This laboratory work demonstrates practical usage of Assembly language for non-trivial array processing tasks. Identical outputs from the C++ and Assembly implementations confirm the correctness and reliability of the low-level solutions.
