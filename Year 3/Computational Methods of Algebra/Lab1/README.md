# Laboratory Work: Numerical Methods for Solving Systems of Linear Equations

## Overview

This repository contains the implementation of a laboratory work on numerical methods for solving systems of linear algebraic equations (SLAE).

The work focuses on solving systems of the form:

\[
Ax=b
\]

using direct and iterative numerical methods, evaluating solution accuracy, and analyzing the numerical properties of the coefficient matrix.

The implementation is done in **C++** using the standard library.

---

## Objectives

- Solve systems of linear algebraic equations using different numerical methods.
- Implement **Gaussian elimination with complete pivoting**.
- Implement the **Left Sweep Method (Thomas Algorithm)** for tridiagonal matrices.
- Implement the **Jacobi iterative method**.
- Implement the **Successive Over-Relaxation (SOR) method**.
- Calculate the determinant and inverse matrix.
- Calculate the condition number of the coefficient matrix.
- Evaluate solution accuracy using residual vectors and matrices.
- Compare numerical methods in terms of accuracy and computational efficiency.

---

## Project Structure

```text
.
├── main.cpp       # Implementation of all numerical methods
├── Input.txt      # Input matrix and right-hand-side vector
├── Output.txt     # Results of numerical calculations
└── README.md      # Project documentation
```

---

## Requirements

- C++11 or higher
- GCC, Clang, or MSVC compiler
- Standard C++ library

No external libraries are required.

---

## Input Data

The program reads input data from `Input.txt`.

The input format consists of:

1. Matrix dimension \(n\).
2. Coefficient matrix \(A\) of size \(n \times n\).
3. Right-hand-side vector \(b\).

**Parameters (Assigned Variant):**

- Matrix dimension: `n = 5`
- Required accuracy: `ε = 10⁻⁵`
- Initial approximation: `x⁰ = b`
- SOR relaxation parameter: `ω = 1.5`
- Maximum number of iterations: `10000`

---

## Implemented Numerical Methods

### 1. Gaussian Elimination with Complete Pivoting

Direct method for solving systems of linear equations.

**Implementation steps:**

1. Find the largest absolute element in the remaining submatrix.
2. Perform row and column permutations to move the selected element to the pivot position.
3. Perform forward elimination.
4. Apply back substitution.
5. Restore the original order of unknown variables.

**Additional calculations:**

- Determinant of matrix \(A\).
- Inverse matrix \(A^{-1}\).
- Condition number.
- Residual vector and its norm.

### 2. Left Sweep Method (Thomas Algorithm)

Direct method designed for solving tridiagonal systems of linear equations.

**Implementation steps:**

1. Check whether the coefficient matrix is tridiagonal.
2. Perform the forward sweep to calculate auxiliary coefficients.
3. Perform backward substitution to obtain the solution.

**Additional calculations:**

- Determinant using the tridiagonal recurrence formula.
- Inverse matrix using repeated applications of the left sweep method.
- Condition number.
- Residual matrix and residual vector.

The method is executed only if the input matrix is tridiagonal.

### 3. Jacobi Iterative Method

Iterative method in which each new approximation is calculated using the values from the previous iteration.

**Parameters:**

- Initial approximation: `x⁰ = b`
- Accuracy: `ε = 10⁻⁵`
- Maximum iterations: `10000`

**Stopping criterion:**

\[
\|x^{(k+1)}-x^{(k)}\|_\infty \leq \varepsilon
\]

The program calculates the final solution, number of iterations, and residual vector.

### 4. Successive Over-Relaxation (SOR) Method

Iterative method based on the Gauss-Seidel approach with an additional relaxation parameter.

**Parameters:**

- Initial approximation: `x⁰ = b`
- Relaxation parameter: `ω = 1.5`
- Accuracy: `ε = 10⁻⁵`
- Maximum iterations: `10000`

**Stopping criterion:**

\[
\|x^{(k+1)}-x^{(k)}\|_\infty \leq \varepsilon
\]

The program calculates the final solution, number of iterations, and residual vector.

---

## Numerical Analysis

The program performs additional calculations to evaluate the accuracy and numerical stability of the obtained results.

### Matrix Determinant

Calculated using Gaussian elimination with complete pivoting.

### Inverse Matrix

Calculated by solving a set of linear systems:

\[
AX=E
\]

where \(E\) is the identity matrix.

### Condition Number

Calculated using the infinity norm:

\[
\kappa_\infty(A)=\|A\|_\infty\cdot\|A^{-1}\|_\infty
\]

### Residual Matrix

\[
R=A^{-1}A-E
\]

The infinity norm of the residual matrix is also calculated.

### Residual Vector

For each numerical method, the residual vector is calculated as:

\[
r=Ax-b
\]

Its infinity norm is used to evaluate the accuracy of the obtained solution:

\[
\|r\|_\infty=\max_i|r_i|
\]

---

## Usage

### Compilation

Using GCC:

```bash
g++ -std=c++17 -O2 main.cpp -o slau
```

### Execution

Make sure `Input.txt` is located in the working directory.

Run the executable:

```bash
./slau
```

On Windows:

```bash
slau.exe
```

The program reads the input data from `Input.txt` and writes all calculation results to `Output.txt`.

---

## Output

The output file contains:

- Gaussian elimination solution.
- Determinant of matrix \(A\).
- Inverse matrix \(A^{-1}\).
- Condition number of matrix \(A\).
- Residual matrix and its norm.
- Residual vector and its norm.
- Left sweep solution and additional calculations (if the matrix is tridiagonal).
- Jacobi method solution and iteration count.
- SOR method solution and iteration count.
- Residual vectors and their norms for iterative methods.

All numerical values are displayed in scientific notation where appropriate.

---

## Results Summary

| Method | Type | Additional Analysis |
|---|---|---|
| Gaussian Elimination | Direct | Determinant, inverse matrix, condition number, residuals |
| Left Sweep | Direct | Determinant, inverse matrix, condition number, residuals |
| Jacobi | Iterative | Number of iterations, residual |
| SOR | Iterative | Number of iterations, residual |

**Note:** The Left Sweep Method requires a tridiagonal coefficient matrix. If the input matrix does not satisfy this condition, the method is automatically skipped.

---

## Conclusion

This laboratory work demonstrates the implementation and comparison of four numerical methods for solving systems of linear algebraic equations.

The program combines direct and iterative approaches and provides additional numerical analysis tools for evaluating solution accuracy, matrix conditioning, and convergence behavior.

The obtained results allow comparison of the implemented methods in terms of numerical accuracy and computational efficiency.