# Lab 6: String and File Processing

## Description

This laboratory work consists of **two independent tasks** related to **string analysis** and **text file processing**. Both tasks are implemented in **one C++ program** using separate functions, while preserving the original algorithm logic.

---

## Task 1. Words with the Maximum Number of Distinct Characters

### Problem Statement

Given an input string containing words separated by a set of delimiters, find **all words that contain the maximum number of distinct characters** and combine them into a new string.

* Words in the input string may be separated by punctuation marks or spaces.
* Words in the resulting string must be separated by **exactly one space**.

### Algorithm Idea

1. Traverse the string **in one pass**, skipping delimiter characters.
2. Extract words by detecting the start and end positions between delimiters.
3. For each word, count the number of **distinct characters**.
4. Determine the maximum number of distinct characters among all words.
5. Concatenate all words that match this maximum into a result string.

### Example

**Input:**

```
BbBb DDDdDD PPPPPPPP nnn
```

**Output:**

```
BbBb DDDdDD
```

---

## Task 2. File Processing and Sorting by Number of Digits

### Problem Statement

Given a text file `Input.txt` consisting of several lines of text:

1. Remove from each line (starting from the second) all words that appear in the **first line**.
2. Write the result to a file `Output.txt`.
3. For each resulting line, sort its words in **ascending order of the number of digits** in each word.
4. Write the sorted lines to a file `Out_sort.txt`.

Words are separated by a set of punctuation characters.

### Algorithm Idea

1. Read and store the first line of the file.
2. For each subsequent line:

    * Remove all occurrences of words that appear in the first line.
    * Save the modified line to `Output.txt`.
3. For sorting:

    * Split each line into words.
    * Count the number of digits in each word.
    * Sort the words using **bubble sort** based on digit count.
    * Write the sorted result to `Out_sort.txt`.

---

## Notes

* Both tasks are implemented in a **single `.cpp` file**.
* The program uses **functions** to clearly separate logic between tasks.
* The original algorithm structure and behavior are fully preserved.
* Standard C++ libraries are used for string manipulation and file I/O.
* Input validation and delimiter handling are included.

---

## Files Used

* `Input.txt` — source text file
* `Output.txt` — file after removing repeated words
* `Out_sort.txt` — file with words sorted by digit count
