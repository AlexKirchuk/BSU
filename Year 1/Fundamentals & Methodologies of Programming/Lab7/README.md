# Lab: Student Records Processing Using Files

## Description

This laboratory work is devoted to processing student records stored in a text file. The program reads student data, calculates individual and overall averages, generates several lists based on academic performance, sorts the results, and writes them to both **binary** and **text** files.

All results are also displayed on the screen for verification.

---

## Problem Statement

A text file is given that contains information about students in the following format:

```
SURNAME GROUP RECORD_BOOK_NUMBER MATH_GRADE GEO_GRADE PROG_GRADE
```

### Example

```
Ivanov 4 456345 5 3 4
Petrov 4 456348 4 3 4
Ivanova 5 456340 5 3 5
Petrova 5 456349 4 5 4
```

It is required to develop a program that generates:

* the **average grade of each student**;
* the **overall average grade**;
* a **general list** containing:

    * surname;
    * group number;
    * record book number;
    * average grade;
* a **list of excellent students** (average grade equal to 5);
* a **list of students with unsatisfactory grades** (at least one grade lower than 4).

---

## Output Requirements

1. All generated lists must be **displayed on the screen**.
2. The lists must be **sorted**:

    * by group number;
    * within each group — by surname in alphabetical order.
3. The following **binary files** must be created:

    * `OutAll.bin` — general sorted list;
    * `OutO.bin` — list of excellent students;
    * `OutN.bin` — list of students with unsatisfactory grades.
4. Data from the binary files must be copied into **text files**:

    * `OutAll.txt`;
    * `OutO.txt`;
    * `OutN.txt`.
5. The **overall average grade** must be written as the **first line** of `OutAll.txt`.

---

## Algorithm Idea

1. Read student data line by line from the input file and store it in a structure.
2. For each student, calculate the individual average grade.
3. Using all students’ data, compute the overall average grade.
4. Generate the required lists:

    * general list;
    * list of excellent students;
    * list of students with unsatisfactory grades.
5. Sort all lists by group number and by surname within each group.
6. Write the sorted data to binary files.
7. Copy the contents of the binary files into the corresponding text files.
8. Output all results to the console for verification.

---

## Notes

* All file operations are performed using standard C++ input/output streams.
* The program demonstrates work with structures, vectors, file processing, sorting algorithms, and aggregation of numerical data.
* The original algorithm logic is preserved.
