# Lab 2 — String Processing with QString

## Description

This laboratory work is devoted to string processing using the **Qt `QString` class**.

The task is based on a string-processing assignment from the first semester and is reimplemented using Qt tools. The program performs file input and output and processes the string in a single pass.

---

## Problem Statement

Given a string containing words separated by an arbitrary set of delimiters, it is required to:

* Find all words that contain the **maximum number of distinct characters**
* Perform the processing in **one pass over the string characters**
* Write the resulting words into a new string
* Separate words in the output string by **exactly one space**

Input is read from a file, and the result is written to an output file.

---

## Input and Output

### Input

A text string read from a file. Words may be separated by spaces or other delimiter characters.

### Output

A string written to a file containing only the words with the maximum number of distinct characters, separated by one space.

---

## Example

**Input:**

```
12212 32221 54434 qwewq wwwwq
```

**Output:**

```
54434 qwewq
```

---

## Implementation Details

* The solution is implemented using the **Qt framework**
* The `QString` class is used for string manipulation
* File input and output are implemented using Qt file streams
* The algorithm processes the string in a single traversal

---

## Purpose of the Lab

* Learn to work with the `QString` class
* Practice string parsing and character analysis
* Apply file-based input and output using Qt
* Reinforce efficient string-processing techniques

---

## Conclusion

This laboratory work demonstrates practical usage of `QString` for efficient string processing and shows how classical string problems can be solved using Qt tools with file input and output.
