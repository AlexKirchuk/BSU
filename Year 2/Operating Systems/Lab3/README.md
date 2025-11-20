# Laboratory Work No. 3 – Synchronization Using Critical Sections, Events, and Deadlock Handling

## Topic: Thread Synchronization with Critical Sections and Events. Deadlock Processing

This laboratory assignment requires implementing a multithreaded console application that demonstrates synchronized work among multiple threads using **critical sections**, **events**, and controlled deadlock resolution. The program is implemented in **CMake**, using **C++98** (with Boost Test) and **C++11** (with Catch2) for testing.

---

## Task Description

The program consists of:

* one **main** thread
* multiple instances of the **marker** thread

The main thread controls lifecycle, synchronization, and deadlock resolution between marker threads.

---

## Main Thread Responsibilities

1. Allocate memory for an integer array (size entered from the console).
2. Initialize all elements of the array to zero.
3. Request from the user the number of marker threads to start.
4. Create the specified number of marker threads, passing each its sequential ID.
5. Send a signal that allows all marker threads to begin their work.
6. Execute a control loop:

   1. Wait until **all** marker threads report that they cannot continue.
   2. Print the current state of the array.
   3. Request the ID of a marker thread that should be terminated.
   4. Send a termination signal to the chosen marker thread.
   5. Wait for this marker thread to finish.
   6. Print the updated array.
   7. Send a "continue" signal to all remaining marker threads.
7. After all marker threads finish, terminate the program.

---

## Marker Thread Responsibilities

1. Begin working only after receiving a start signal from the main thread.
2. Initialize the random number generator using:

   ```cpp
   srand(data->id);
   ```
3. Execute the following in a cycle:

   1. Generate a random number using `rand()`.
   2. Compute an array index as `(random_number % size)`.
   3. If the array element at that index is **0**:

      * Sleep for 5 ms.
      * Write its thread ID into the element.
      * Sleep for 5 ms.
      * Continue the loop.
   4. Otherwise (the element is already marked):

      * Print:

        * its thread ID
        * number of elements it has marked so far
        * the index it could not mark
      * Signal the main thread about inability to continue.
      * Wait for a signal from the main thread: continue or terminate.
4. If a termination signal is received:

   * Reset all elements previously marked by this thread back to **0**.
   * Exit.
5. If a continue signal is received:

   * Resume the main loop.

---

## Synchronization Requirements

* Use **critical sections** to protect shared array access.
* Use **events** to signal:

  * start of work
  * inability to continue
  * continuation permission
  * termination instruction
* Ensure proper handling of thread deadlock situations during synchronization.

---

## Project Structure (CMake)

```
project-root/
├── include/
│   ├── array.h
│   ├── catch.h
│   └── marker.h
├── src/
│   ├── array.cpp
│   ├── main.cpp
│   └── marker.cpp
├── tests/
│   ├── test.cpp
│   └── CMakeLists.txt
└── CMakeLists.txt
```

---

## Technologies Used

### Runtime Implementation

* **C++98**
* Windows API:

  * Critical Sections
  * Events
  * Sleep
  * rand()

* **C++11**
* Windows API:

  * std::thread
  * std::lock_guard
  * std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP))
  * std::mt19937

### Testing

* **Boost.Test** for C++98
* **Catch2** for C++11 variant

---

## Build Instructions

### CMake Build

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Execution Workflow Example

1. User inputs array size.
2. User inputs number of marker threads.
3. Threads begin marking random positions.
4. When threads block, the main thread:

   * displays array
   * selects a thread for termination
   * updates array
   * resumes remaining threads
5. Process repeats until all marker threads are terminated.

---

## Testing

Tests are located in the `/tests` directory.

* C++98: Boost Test
* C++11: Catch2

To run all tests:

```sh
ctest
```

---

## License

This project is provided for educational use in the topic of multithreading, synchronization, and deadlock processing.