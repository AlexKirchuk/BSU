# Lab 1 — Introduction to Qt

## Description

This laboratory work is an introduction to cross-platform application development using **C++** and the **Qt framework**.

The main objective of the lab is to practice object-oriented programming and to compare two approaches to implementation:

* Using the **C++ Standard Library (STL)**
* Using **Qt containers and streams**

The lab includes the implementation of three core classes: `Number`, `Array`, and `Matrix`.

---

## Implemented Classes

### Number

The `Number` class works with an integer value and provides methods for performing various numeric operations.

**Key functionality:**

* Calculating the sum of cubes of digits
* Finding pairs of numbers divisible by 5
* Finding all divisors of a number
* Calculating the product of digit pairs
* Kaprekar transformation

Input and output are implemented using stream operators.

---

### Array

The `Array` class represents a one-dimensional collection of integers.

**Key functionality:**

* Checking whether the sequence is arithmetic or geometric
* Removing duplicate elements
* Sorting unique elements
* Finding the intersection with another array

The class demonstrates work with dynamic containers and algorithms.

---

### Matrix

The `Matrix` class represents a two-dimensional numeric structure.

**Key functionality:**

* Finding positive elements in the matrix
* Smoothing the matrix values using neighboring elements

This class demonstrates working with nested containers and matrix processing.

---

## Implementation Variants

The project contains **two independent implementations** of all classes:

### STL Version

* Containers: `std::vector`
* Input/output: `std::istream`, `std::ostream`
* Headers: `<vector>`, `<iostream>`

### Qt Version

* Containers: `QVector`
* Input/output: `QTextStream`
* Debug output: `QDebug`

This separation allows a direct comparison between standard C++ tools and Qt tools.

---

## Purpose of the Lab

* Learn the basics of Qt containers and streams
* Practice operator overloading
* Strengthen understanding of classes and encapsulation
* Compare STL and Qt approaches in cross-platform development

---

## Conclusion

This laboratory work provides hands-on experience with both STL and Qt, helping to understand their differences, advantages, and typical use cases in real-world cross-platform applications.
