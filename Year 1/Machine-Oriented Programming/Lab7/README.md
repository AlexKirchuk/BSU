# Lab 7 — String Processing

## Task Description

During a single pass through the characters of a string, find all words that contain the **maximum number of distinct characters** and place them into a new string.

* Words in the original string are separated by an arbitrary set of delimiters.
* Words in the resulting string must be separated by **exactly one space**.

The task must be solved in **one pass over the string characters**.

---

## Input

A single line of text containing words separated by delimiters (spaces, punctuation marks, etc.).

## Output

A new string consisting of all words that contain the largest number of distinct characters.

---

## Test Cases

### Test 1

**Input string:**

```
Да будет славен, ФПМ, во все времена!!!
```

**Result:**

```
Resulting string: славен времена
```

---

### Test 2

**Input string:**

```
За один просмотр символов строки найти все слова,
```

**Result:**

```
Resulting string: просмотр символов строки
```

---

### Test 3

**Input string:**

```
FAMCS is a brand in IT in B E L A R U S and abroad!
```

**Result:**

```
Resulting string: FAMCS brand abroad
```

---

### Test 4

**Input string:**

```
BbBb DDDdDD PPPPPPPP nnn
```

**Result:**

```
Resulting string: BbBb DDDdDD
```

---

## Notes

* Character case matters (`A` and `a` are considered different characters).
* Only alphabetic characters are considered part of words; delimiters are ignored.
* The solution processes the string sequentially without revisiting characters.
