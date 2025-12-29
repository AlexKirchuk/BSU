# Colloquium No. 1 – Industrial-Grade C++ Development

## Topic: Algorithmic Problems with Production-Level Quality

This colloquium assignment focuses on implementing classical algorithmic problems using **industrial-grade C++ code**. The solution emphasizes correctness, robustness, clean design, exception safety, and comprehensive test coverage.

The project is implemented using **CMake**, **C++17**, **Google Test** for unit testing, and a **REST API** (⭐ advanced task) built with **cpp-httplib**, complemented by **Python-based API tests**.

---

## General Requirements

* Use clean, modular, and maintainable C++ code
* Validate all inputs
* Handle special and exceptional cases
* Cover functionality with unit tests
* Follow production-level coding practices

---

## Problem Variants

### Odd Variant (Implemented)

1. **Factorial Sequence**

   * Input: a natural number `n`
   * Output: a container holding the first `n` factorials

2. **Remove Duplicates**

   * Input: a container (array) of numbers
   * Output: a container with the same element order, but without duplicate values

3. **Reverse a Linked List (Recursive)**

   * Reverse a singly linked list using a recursive approach

---

### Even Variant

1. **Fibonacci Sequence**

   * Input: a natural number `n`
   * Output: a container holding the first `n` Fibonacci numbers

2. **Palindrome Check**

   * Input: an integer number
   * Output: boolean result indicating whether the number is a palindrome

3. **Reverse a Linked List (Iterative)**

   * Reverse a singly linked list using an iterative approach

---

## ⭐ Advanced Task: REST API Service

As an advanced extension, the solution is implemented as a **RESTful service**:

* Each algorithm is exposed via HTTP endpoints
* Requests and responses use JSON format
* The service is implemented using **cpp-httplib**
* API correctness is verified using **Python-based tests**

---

## Project Structure (CMake)

```
project-root/
├── include/
│   ├── factorial.h
│   ├── linked_list.h
│   └── unique.h
├── src/
│   ├── main.cpp
│   ├── server.cpp
│   ├── factorial.cpp
│   ├── linked_list.cpp
│   └── unique.cpp
├── tests/
│   ├── test_factorial.cpp
│   ├── test_linked_list.cpp
│   ├── test_unique.cpp
│   ├── test_api.py
│   └── requirements.txt
└── CMakeLists.txt
```

---

## Technologies Used

### Runtime Implementation

* **C++17**
* Standard Template Library (STL)
* Exception handling
* Clean separation of logic and interface

### REST API

* **cpp-httplib** for HTTP server
* JSON-based request/response format

### Testing

* **Google Test** for C++ unit tests
* **Python** API tests (HTTP-level validation)

---

## Build Instructions

### Build with CMake

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Running the Application

### Console Application

```sh
./colloquium_app
```

### REST Server

```sh
./server
```

---

## Testing

### C++ Unit Tests

```sh
ctest
```

### API Tests

```sh
pip install -r tests/requirements.txt
pytest tests/test_api.py
```

---

## License

This project is intended for educational purposes within the colloquium on industrial-quality C++ development.