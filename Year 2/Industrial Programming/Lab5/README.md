# Lab 5 — Classes, Interfaces: `Iterator<T>`/`Iterable<T>`, `Comparable<T>`/`Comparator<T>`

Develop a **Java console application** with the following tasks:

1. **Create the specified class(es)**. Use `assert` and exceptions where appropriate to handle erroneous situations.

2. **Develop a separate test application** that uses the specified class(es).  
   Test all constructors and methods, and output the results and data.

---

## Variant 7 — Triangle Class Hierarchy

1. **Abstract Base Class `Triangle`**  
   Represents a triangle with the following features:  
   - Data fields: **two sides** and the **angle between them**  
   - Abstract methods to **compute area** and **perimeter**

2. **Derived Class — Equilateral Triangle**  
   Implements the area and perimeter calculations.  
   Additionally stores:  
   - **Outline color**  
   - **Fill color**

3. **Class Requirements:**  
   - Implement `Comparable` and `Comparator` interfaces, allowing comparison by a selected field  
   - Implement `Iterable` interface — indexer over all object fields  
   - Method to save all field values as a **text string** (override `toString()`)  
   - Constructor or method to initialize an object from a text string corresponding to `toString()` output

4. **Console Application:**  
   - Demonstrate usage of the class  
   - Create a small array of objects and print them **sorted by a chosen field**