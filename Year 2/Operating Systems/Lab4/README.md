# Laboratory Work No. 4 – Process Synchronization

## Topic: Process Synchronization

This laboratory work focuses on interprocess communication using a shared binary file. The program consists of one **Receiver** process and multiple **Sender** processes. Senders transmit messages to the Receiver, which reads them in a synchronized FIFO manner.

The project is implemented using **CMake**, with **C++98** for core logic, **C++20** features where applicable, and **Google Test** for unit testing.

---

## Task Description

### Receiver Process Requirements

1. Read from console the name of the binary file and the number of records it will contain.
2. Create a binary file to store messages. Maximum message length: 20 characters.
3. Read from console the number of Sender processes to start.
4. Launch the specified number of Sender processes, passing each the binary file name via the command line.
5. Wait for a ready signal from all Sender processes.
6. Loop to perform the following commands from the console:

   * Read a message from the binary file.
   * Terminate execution.

> Note: If the Receiver attempts to read from an empty file, it waits until a new message arrives.

### Sender Process Requirements

1. Open the binary file specified via the command line.
2. Signal the Receiver that it is ready.
3. Loop to perform the following commands from the console:

   * Send a message to the Receiver.
   * Terminate execution.

> Note: If the Sender attempts to write to a full file, it waits until space becomes available.

### Additional Requirements

* Message transfer through the binary file must be organized as a **FIFO circular queue**.
* Receiver reads messages in the order they were sent by the Sender processes.
* Maximum message length: 20 characters.

---

## Project Structure (CMake)

```
project-root/
├── include/
│   └── common.h
├── src/
│   ├── receiver.cpp
│   └── sender.cpp
├── tests/
│   ├── test.cpp
│   └── CMakeLists.txt
└── CMakeLists.txt
```

---

## Technologies Used

### Runtime Implementation

* **C++98**
* **C++20** (optional modern features)
* Windows API for process creation and synchronization
* File I/O for binary message transfer
* Circular FIFO queue logic for messaging

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

Executables and tests will be located in the build directory.

---

## Running the Application

1. Start the Receiver process and enter the file name, record count, and number of Sender processes.
2. Each Sender process starts and signals readiness.
3. Receiver and Sender processes can send/read messages according to console commands.
4. All messages are processed in **FIFO** order.

---

## Testing

Tests are located in `/tests` and use Google Test.
Run all tests with:

```sh
ctest
```

---

## License

This project is provided for educational purposes on process synchronization and interprocess communication.