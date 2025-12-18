# Laboratory Work No. 5 – Data Exchange via Named Pipes

## Topic: Data Exchange Using Named Pipes

This laboratory work focuses on organizing controlled access of multiple parallel processes to a shared binary file using **named pipes**. The system follows a classic **client–server architecture**, where a single server process manages access to the file and multiple client processes request read or write operations.

The project is implemented using **CMake**, supports **C++98** and **C++23**, and uses **Google Test** for testing.

---

## Task Description

### 1. Server Process Requirements

The server process must perform the following actions:

1. Create a binary file whose records have the following structure:

   ```cpp
   struct employee {
       int num;        // employee ID
       char name[10];  // employee name
       double hours;   // number of hours worked
   };
   ```

   The file name and initial employee data are entered from the console.

2. Output the created binary file to the console.

3. Launch a specified number of **Client** processes. The number of client processes is entered from the console.

4. Serve requests from client processes through named pipes according to the following rules:

   * If a client requests **modification** of a record, access to this record is **exclusively locked** for all other clients until the modification is completed.
   * If a client requests **read-only** access:

     * Other read requests are allowed concurrently.
     * Write (modification) requests are blocked until all read operations are finished.

5. After all client processes have completed their work, output the modified binary file to the console.

6. Terminate execution upon a console command.

---

### 2. Client Process Requirements

Each client process performs the following actions:

1. Execute a loop in which it requests from the console one of the following operations:

   * Modify a record
   * Read a record
   * Exit

2. File access is performed using a **key**, which is the employee ID.

3. When modifying a record, the client:

   1. Requests the record key (employee ID).
   2. Sends a modification request to the server.
   3. Displays the received record on the console.
   4. Requests new field values from the user.
   5. Sends the modified record to the server upon user command.
   6. Ends access to the record upon user command.

4. When reading a record, the client:

   1. Requests the record key (employee ID).
   2. Sends a read request to the server.
   3. Displays the received record on the console.
   4. Ends access to the record upon user command.

---

## Synchronization Rules

* Communication between server and clients is implemented using **named pipes**.
* The server enforces **reader–writer synchronization**:

  * Multiple readers may access the same record simultaneously.
  * Writers obtain exclusive access to records.
* All access conflicts are resolved centrally by the server.

---

## Project Structure (CMake)

```
project-root/
├── include/
│   └── employee.h
├── src/
│   ├── server.cpp
│   └── client.cpp
├── tests/
│   ├── test.cpp
│   └── CMakeLists.txt
└── CMakeLists.txt
```

---

## Technologies Used

### Runtime Implementation

* **C++98**
* **C++23** (modern language features where applicable)
* Windows API:

  * Named Pipes
  * Process management
  * Synchronization primitives

### Testing

* **Google Test** framework

---

## Build Instructions

### Using CMake

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

Executables and tests will be generated in the build directory.

---

## Execution Workflow Example

1. Server creates and displays the initial binary file.
2. Server starts multiple client processes.
3. Clients request read or write access through named pipes.
4. Server enforces access rules and synchronizes file operations.
5. After all clients exit, the server prints the final state of the file.

---

## Testing

Unit tests are located in the `/tests` directory and use Google Test.

Run all tests with:

```sh
ctest
```

---

## License

This project is provided for educational purposes in the context of interprocess communication and synchronization using named pipes.