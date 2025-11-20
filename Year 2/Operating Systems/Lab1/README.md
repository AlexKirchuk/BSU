# Laboratory Work No. 1 – Process Creation

## Topic: Creating Processes

This laboratory work consists of implementing three console applications in C++98 using CMake, Microsoft Visual Studio, and Google Test. The project demonstrates interprocess interaction by running external utilities, transferring data via command-line arguments, and synchronizing processes using `WaitForSingleObject()`.

---

## Task Description

You must implement a main application **Main** and two utility programs: **Creator** and **Reporter**.

### 1. Utility: Creator

The **Creator** tool is responsible for generating a binary file. It receives the following command-line parameters:

* The name of the binary file to create.
* The number of employee records to write.

Each record is input from the console and has the following structure:

```cpp
struct employee
{
    int num;        // employee ID
    char name[10];  // employee name
    double hours;   // number of hours worked
};
```

The program writes the entered records into the binary file.

---

### 2. Utility: Reporter

The **Reporter** tool reads the binary file created by Creator and generates a formatted text report. It receives:

1. Name of the source binary file.
2. Name of the output text report file.
3. Payment rate (salary per hour).

The report must include:

1. A header: `Report for file "<binary filename>"`.
2. A table header: employee number, name, hours worked, calculated salary.
3. A list of employees with salary computed as:

```
salary = hours × payment
```

---

### 3. Main Program Behavior

The main application performs the following steps:

1. Asks the user for the binary filename and number of records.
2. Launches the **Creator** process and passes parameters to it.
3. Waits for the Creator process to finish using:

   ```cpp
   WaitForSingleObject(hCreator, INFINITE);
   ```
4. Displays the contents of the generated binary file.
5. Requests:

   * Report filename
   * Hourly payment rate
6. Launches the **Reporter** process, passing required parameters.
7. Waits for the Reporter process to finish.
8. Outputs the generated report to the console.
9. Terminates.

---

## Project Structure (CMake)

```
project-root/
├── include/
│   └── employee.h
├── src/
│   ├── creator.cpp
│   ├── employee.cpp
│   ├── main.cpp
│   └── reporter.cpp
├── tests/
│   ├── test.cpp
│   └── CMakeLists.txt
└── CMakeLists.txt
```

---

## Technologies Used

* **C++98**
* **CMake** (project configuration)
* **Microsoft Visual Studio** (build environment)
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

Executables will be placed in the build directory.

---

## Running the Applications

### Step 1 — Run Main

This program will:

* request data for the binary file
* start Creator
* display binary file content
* request data for the report
* start Reporter
* display the final report

Example:

```
Enter binary file name: employees.bin
Enter number of employees: 3

Binary file content:
1 Alex 2
2 Vladimir 5
3 Gaben 0

Enter report file name: report.txt
Enter hourly payment: 10.5

Report:
Report based on file "employees.bin"
=========================================
Num     Name    Hours   Salary
2       Vlaimi  5       52.5
1       Alex    2       21
3       Gaben   0       0
```

---

## Testing

Tests are located in the `/tests` directory and use Google Test.
To run tests:

```sh
ctest
```

---

## License

This project is provided for educational purposes within the laboratory work on process creation.