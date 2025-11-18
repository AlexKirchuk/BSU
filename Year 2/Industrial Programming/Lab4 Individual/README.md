# Lab 4 — Individual Assignment: Classes, Collections, Make Utility

Develop a **Java console application** with the following tasks:

1. **Create the specified class** using `assert` and exceptions where appropriate to handle erroneous situations.

2. **Develop a separate test application** that uses the specified class.  
   Test all constructors and methods, and output the results and data.

3. **Create a Makefile** with the following targets:  
   - `clean` — remove intermediate files  
   - `build` — recompile all classes and create an executable JAR  
   - `run` — execute the JAR file

---

## Variant 7 — Interval Class

Define a class `Interval` that stores the **left and right boundaries** of an interval.  
Implement several constructors and methods, including:

- **Length of the interval**  
- **Shift the interval** (left or right)  
- **Scale the interval** (compression or expansion) by a given factor  
- **Compare two intervals**  
- **Sum and difference of two intervals**