# Lab 8 — Working with a Number Class in C++

## Description

This laboratory work is an object-oriented implementation of **Lab 2**, using a custom **Number class**. The program demonstrates the use of:

* classes and objects;
* constructors and a destructor;
* class methods;
* operator overloading for input (`>>`) and output (`<<`).

All tasks from the previous laboratory are preserved, but are now implemented through class methods.

---

## Task Statement

Implement Lab 2 using a class-based approach.

The program must support the following tasks:

1. Find the **smallest and largest three-digit numbers** whose **sum of cubes of digits** is equal to a given number *M*.
2. Find **two five-digit numbers** whose product is equal to **123456789**.
3. Find all **divisors of a given number**.
4. Find pairs of **natural numbers not exceeding N** whose product contains the digits of the larger multiplier separated by zeros.
5. Determine whether a given number is a **Kaprekar number**.

All input and output operations must be performed using **overloaded operators**.

---

## Algorithm Idea

* A `Number` class is created to store and process integer values.
* Each task is implemented as a separate **class method**.
* Constructors initialize the number, and the **destructor outputs a message** when it is called.
* Input and output operators (`>>`, `<<`) are overloaded for convenient interaction with objects.
* All calculations are performed using the class methods without direct access to internal data.

---

## Test Example

```
1. Enter 9
Min = 102
Max = 210

2. No input required
10821 11409

2.1. Enter 100
1 2 4 5 10 20 25 50 100

3. Enter 7
7 1
6 1
5 1
4 1
3 1
2 1
1 1

4. Enter 45
The number is a Kaprekar number

(Destructor called)
(Destructor called)
(Destructor called)
(Destructor called)
(Destructor called)
```

---

## Notes

* The program uses object-oriented programming principles.
* Each task is encapsulated in a class method.
* Destructor calls are displayed to demonstrate object lifecycle management.
* The implementation is suitable for educational purposes and reinforces OOP concepts in C++.
