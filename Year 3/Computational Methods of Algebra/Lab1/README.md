# Laboratory Work: Numerical Methods for Solving Systems of Linear Equations

## Overview

This repository contains the implementation of a laboratory work on numerical methods for solving systems of linear algebraic equations (SLAE).

The work focuses on solving systems of the form:

**Ax = b**

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

- C++17 or higher
- GCC, Clang, or MSVC compiler
- Standard C++ library

No external libraries are required.

---

## Input Data

The program reads input data from `Input.txt`.

The input format consists of:

1. Matrix dimension `n`.
2. Coefficient matrix `A` of size `n x n`.
3. Right-hand-side vector `b`.

**Parameters (Assigned Variant):**

| Parameter | Value |
|---|---|
| Matrix dimension | `n = 5` |
| Required accuracy | `epsilon = 10^-5` |
| Initial approximation | `x^(0) = b` |
| SOR relaxation parameter | `omega = 1.5` |
| Maximum iterations | `10000` |
| Pivot threshold | `10^-15` |

---

## Implemented Numerical Methods

### 1. Gaussian Elimination with Complete Pivoting

A direct method for solving systems of linear equations.

**Implementation steps:**

1. Find the largest absolute element in the remaining submatrix.
2. Perform row and column permutations to move the selected element to the pivot position.
3. Perform forward elimination.
4. Apply back substitution.
5. Restore the original order of unknown variables.

**Additional calculations:**

- Determinant of matrix `A`.
- Inverse matrix `A^-1`.
- Condition number.
- Residual vector and its norm.

### 2. Left Sweep Method (Thomas Algorithm)

A direct method designed for solving tridiagonal systems of linear equations.

**Implementation steps:**

1. Check whether the coefficient matrix is tridiagonal.
2. Perform the forward sweep to calculate auxiliary coefficients.
3. Perform backward substitution to obtain the solution.

**Additional calculations:**

- Determinant using the tridiagonal recurrence formula.
- Inverse matrix using repeated applications of the left sweep method.
- Condition number.
- Residual matrix and residual vector.

The method is executed only if the input matrix is tridiagonal. Otherwise, it is automatically skipped.

### 3. Jacobi Iterative Method

An iterative method in which each new approximation is calculated using the values from the previous iteration.

**Iteration formula:**

```text
x_i^(k+1) = (b_i - sum(a_ij * x_j^(k))) / a_ii
```

where the summation is performed for all `j != i`.

**Parameters:**

- Initial approximation: `x^(0) = b`
- Accuracy: `epsilon = 10^-5`
- Maximum iterations: `10000`

**Stopping criterion:**

```text
||x^(k+1) - x^(k)||_inf <= epsilon
```

The program calculates the final solution, number of iterations, and residual vector.

### 4. Successive Over-Relaxation (SOR) Method

An iterative method based on the Gauss-Seidel approach with an additional relaxation parameter.

**Iteration formula:**

```text
x_i^(k+1) = (1 - omega) * x_i^(k) + omega * x_i_GS
```

where `x_i_GS` is calculated using the most recently available values:

```text
x_i_GS = (b_i - sum(j < i, a_ij * x_j^(k+1))
             - sum(j > i, a_ij * x_j^(k))) / a_ii
```

**Parameters:**

- Initial approximation: `x^(0) = b`
- Relaxation parameter: `omega = 1.5`
- Accuracy: `epsilon = 10^-5`
- Maximum iterations: `10000`

**Stopping criterion:**

```text
||x^(k+1) - x^(k)||_inf <= epsilon
```

The program calculates the final solution, number of iterations, and residual vector.

---

## Numerical Analysis

The program performs additional calculations to evaluate the accuracy and numerical stability of the obtained results.

### Matrix Determinant

The determinant of matrix `A` is calculated using Gaussian elimination with complete pivoting.

### Inverse Matrix

The inverse matrix is calculated by solving a set of linear systems:

```text
A * X = E
```

where `E` is the identity matrix.

### Condition Number

The condition number is calculated using the infinity norm:

```text
kappa_inf(A) = ||A||_inf * ||A^-1||_inf
```

The matrix infinity norm is defined as:

```text
||A||_inf = max_i(sum_j(|a_ij|))
```

A larger condition number indicates that the system may be more sensitive to perturbations in the input data.

### Residual Matrix

The residual matrix is calculated as:

```text
R = A^-1 * A - E
```

The infinity norm of the residual matrix is also calculated to evaluate the accuracy of the inverse matrix.

### Residual Vector

For each obtained solution, the residual vector is calculated as:

```text
r = A * x - b
```

Its infinity norm is:

```text
||r||_inf = max_i(|r_i|)
```

A smaller residual norm indicates that the obtained solution satisfies the original system more accurately.

---

## Usage

### Compilation

Using GCC:

```bash
g++ -std=c++17 -O2 main.cpp -o slau
```

### Execution

Make sure `Input.txt` is located in the working directory of the executable.

Run the program:

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
- Determinant of matrix `A`.
- Inverse matrix `A^-1`.
- Condition number of matrix `A`.
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

**Note:** The Left Sweep Method requires a tridiagonal coefficient matrix. The assigned matrix is not tridiagonal, so this method is automatically skipped for the provided input data.

---

## Conclusion

This laboratory work demonstrates the implementation and comparison of four numerical methods for solving systems of linear algebraic equations.

The program combines direct and iterative approaches and provides additional numerical analysis tools for evaluating solution accuracy, matrix conditioning, and convergence behavior.

The obtained results allow comparison of the implemented methods in terms of numerical accuracy and computational efficiency.