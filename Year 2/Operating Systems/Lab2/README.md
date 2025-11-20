# Laboratory Work No. 2 – Thread Creation

## Topic: Creating Threads

This laboratory work requires implementing a console application that uses multithreading to process an integer array. The project is implemented using **CMake**, **C++98 / C++17**, and the **doctest** testing framework.

---

## Task Description

The program consists of one console process and three threads:

* main thread
* min_max thread
* average thread

### 1. Main Thread Responsibilities

1. Create an integer array (size and elements are entered from the console).
2. Create the `min_max` and `average` threads.
3. Wait for both threads to finish.
4. Replace the minimum and maximum array elements with the computed average value.
5. Print the updated array.
6. Terminate the program.

---

### 2. `min_max` Thread Responsibilities

1. Identify the minimum and maximum values in the array.
2. Print the found values to the console.
3. After each comparison, pause for **7 milliseconds**.
4. Terminate its execution.

---

### 3. `average` Thread Responsibilities

1. Compute the arithmetic mean of all array elements.
2. Print the average to the console.
3. After each addition, pause for **12 milliseconds**.
4. Terminate its execution.

---

## Synchronization

The main thread must wait for the completion of other threads using:

```cpp
WaitForSingleObject(hThread, INFINITE);
```

where `hThread` is the thread handle.

Pausing during calculations is done using:

```cpp
Sleep(ms);
```

---

## Project Structure (CMake)

```
project-root/
├── include/
│   ├── average.h
│   ├── data.h
│   ├── doctest.h
│   └── minmax.h
├── src/
│   └── main.cpp
├── libs/
│   ├── datalib/
│   │   └── data.cpp
│   ├── doctest/
│   │   ├── doctest.cpp
│   │   └── doctest_fwd.h
│   └── threadlib/
│       ├── average.cpp
│       └── minmax.cpp
├── tests/
│   ├── test_threads.cpp
│   └── CMakeLists.txt
└── CMakeLists.txt
```

---

## Technologies Used

* **C++98**
* **C++17**
* **CMake**
* **doctest** testing framework
* Windows API threads (`CreateThread`, `WaitForSingleObject`, `Sleep`)

---

## Build Instructions

### Using CMake

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Running the Program

Example console session:

```
Enter array size: 5
Enter array elements: 4 10 -1 3 9
Average: 5
Minimum: -1
Maximum: 10
Modified array: 4 5 5 3 9
```

---

## Testing

Tests are located in the `/tests` directory and use doctest.
To run tests:

```sh
ctest
```

---

## License

This project is intended for educational purposes within the module on thread creation.