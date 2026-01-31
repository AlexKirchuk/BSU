# Lab 10 — STL Containers: List, Queue, Stack

## Description

This laboratory work demonstrates practical usage of Standard Template Library (STL) containers in C++. The program solves three independent tasks using `list`, `deque` (queue), and `stack`. File input/output is used, and each task is implemented as a separate function for clarity and modularity.

## Tasks Overview

### Task 1 — List Processing

**Condition:**
The file `InputList.txt` contains a sequence of integers.

**Requirements:**

* Read all integers into a list.
* Compare elements pairwise and remove duplicates (if an element appears again later, only one occurrence is kept).
* Write the resulting list to `OutputList.txt`.

**Algorithm Idea:**
For each element in the list, check whether the same value exists further in the list. If no duplicate is found, add the element to a new list.

---

### Task 2 — Customer Queue Simulation

**Condition:**
A queue of customers is waiting at a checkout counter. Each customer has an ID and a number of purchases.

**Input:**

* `n` — initial number of customers
* `m` — number of already served customers
* `k` — minutes before the cashier goes on break
* `mt` — seconds required to process one item
* `pt` — seconds required to print a receipt

Customer data is read from `InputQueue.txt`.

**Requirements:**

* Remove the first `m` customers from the queue.
* Simulate customer service until time runs out.
* If all customers are served before the break, output `Yes`.
* Otherwise, output `No` and print the list of remaining customers.
* Write results to `OutputQueue.txt`.

**Algorithm Idea:**
Calculate the remaining time in seconds. For each customer, subtract the service time. If time becomes negative, stop processing and output remaining customers.

---

### Task 3 — Stack Processing

**Condition:**
The file `InputStack.txt` contains a sequence of integers.

**Requirements:**

* Read all numbers into a stack.
* Remove all odd numbers.
* Write the remaining even numbers to `OutputStack.txt`.

**Algorithm Idea:**
Pop elements from the original stack. If the number is even, push it into a new stack. Output the result stack.

---

## Program Structure

* `taskList()` — solves Task 1 using `std::list`
* `taskQueue()` — solves Task 2 using `std::deque`
* `taskStack()` — solves Task 3 using `std::stack`
* `main()` — sequentially calls all tasks

## Used STL Containers

* `std::list`
* `std::deque`
* `std::stack`

## Input / Output Files

* `InputList.txt`, `OutputList.txt`
* `InputQueue.txt`, `OutputQueue.txt`
* `InputStack.txt`, `OutputStack.txt`

## Conclusion

This lab demonstrates working with STL containers, file I/O operations, and basic algorithmic logic. The solution is modular, readable, and follows standard C++ practices.
