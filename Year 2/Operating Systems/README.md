# Operating Systems — Industrial Programming Lab Collection

This repository contains a comprehensive collection of **Operating Systems** laboratory works and colloquiums, implemented using **industrial-grade programming practices**.

The projects focus on **processes, threads, synchronization, interprocess communication, and system-level programming**, with strong emphasis on correctness, robustness, and test coverage.

All implementations are written in **C++** and follow modern software engineering standards, including **error handling**, **synchronization safety**, and **unit testing**.

---

## Overview

- Total of **5 laboratory works** and **2 colloquiums**
- All labs are implemented as **independent projects**
- Each assignment demonstrates a specific Operating Systems concept
- Projects include **unit tests**, and some include **integration / API tests**
- Advanced tasks are implemented as **REST services**

The repository reflects a **progressive learning path**, starting from basic process creation and ending with advanced interprocess communication and distributed-style services.

---

## Development Environment

- **C++ standards**:  
  - C++98 (low-level OS concepts, Windows API)  
  - C++11 / C++17 / C++20 / C++23 (modern abstractions and testing)
- **Build system**: CMake
- **IDE**:
  - **Microsoft Visual Studio 2026** — C++ development
  - **PyCharm** — Python-based API testing (Colloquium 2)
- **Testing frameworks**:
  - Google Test
  - Boost.Test
  - Catch2
  - doctest
- **Additional technologies**:
  - Windows API
  - Named Pipes
  - REST APIs
  - Docker (Colloquium 2)

---

## Laboratory Works

### **Lab 1 — Process Creation**
- Creating and managing processes
- Interprocess execution control
- Process synchronization using `WaitForSingleObject`
- Binary file generation and reporting
- Windows API process management

---

### **Lab 2 — Thread Creation**
- Multithreaded applications
- Thread synchronization
- Shared memory access
- Artificial delays using `Sleep`
- Comparison of thread workloads

---

### **Lab 3 — Thread Synchronization and Deadlock Handling**
- Critical sections and events
- Multiple worker threads
- Deadlock simulation and resolution
- Controlled thread termination
- Fine-grained synchronization logic

---

### **Lab 4 — Process Synchronization**
- Interprocess communication via shared binary file
- FIFO circular queue
- Producer–consumer model
- Multiple sender processes and one receiver process
- Blocking and waiting semantics

---

### **Lab 5 — Data Exchange via Named Pipes**
- Client–server architecture
- Named pipes for IPC
- Concurrent file access control
- Reader–writer synchronization
- Centralized access management

---

## Colloquiums

### **Colloquium 1 — Industrial-Grade Algorithmic Development**
- Production-quality C++ solutions
- Input validation and exception safety
- Unit test coverage (Google Test)
- Algorithms:
  - Factorials / Fibonacci
  - Removing duplicates
  - Linked list reversal (recursive & iterative)
- ⭐ Advanced task:
  - REST API implementation using **cpp-httplib**
  - Python-based API tests

---

### **Colloquium 2 — Industrial-Grade REST API Development**
- Full-stack REST API
- Backend: **Python + FastAPI**
- Frontend: **Vue 3 + Vite**
- Authentication and authorization (JWT)
- Fault tolerance:
  - Database
  - Cache (Redis)
  - Task queue (Celery)
- Metrics and logging (Prometheus)
- Dockerized deployment
- Extensive automated testing

---

## Key Concepts Covered

- Processes and threads
- Synchronization primitives
- Deadlocks and race conditions
- Interprocess communication (IPC)
- Named pipes
- Reader–writer problem
- RESTful services
- Fault-tolerant system design
- Industrial testing practices

---

## Purpose of This Repository

This repository serves as:

- A **complete reference** for Operating Systems programming
- A demonstration of **industrial-grade C++ development**
- A portfolio-ready collection of **system-level projects**
- A foundation for advanced backend and systems engineering

---

## License

Educational projects developed as part of the **Operating Systems** course.