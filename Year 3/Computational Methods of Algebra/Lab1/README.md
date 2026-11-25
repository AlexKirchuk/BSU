# Laboratory Work: Numerical Methods for Solving Systems of Linear Algebraic Equations

## Overview

This repository contains the implementation of a laboratory work on numerical methods for solving systems of linear algebraic equations (SLAE).

The work focuses on solving systems of the form:

$$Ax=b$$

using direct and iterative numerical methods, evaluating solution accuracy, and analyzing the numerical properties of the coefficient matrix.

The implementation is done in **C++** using the standard library. All numerical algorithms are implemented manually without external mathematical libraries.

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
- Analyze the convergence of iterative methods.
- Compare numerical methods in terms of accuracy and computational efficiency.

---

## Project Structure

```text
.
├── main.cpp       # Implementation of all numerical methods
├── Input.txt      # Input matrix and right-hand-side vector
├── Output.txt     # Results of numerical calculations
└── README.md      # This file
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

1. Matrix dimension $n$.
2. Coefficient matrix $A$ of size $n \times n$.
3. Right-hand-side vector $b$.

**Parameters (Assigned Variant):**

| Parameter | Value | Description |
|-----------|-------|-------------|
| $n$ | 5 | Matrix dimension |
| $\varepsilon$ | $10^{-5}$ | Required accuracy |
| $x^{(0)}$ | $b$ | Initial approximation |
| $\omega$ | 1.5 | SOR relaxation parameter |
| $N_{\max}$ | 10000 | Maximum number of iterations |
| $\delta$ | $10^{-15}$ | Pivot threshold |

**Input format example:**

```text
5
0.7914  0.0000 -0.2067  0.1454  0.2423
-0.0485 0.5168  0.0000 -0.0985  0.0323
0.0162 -0.1454  0.9367  0.0178  0.0565
0.0485  0.0000 -0.1179  0.9367  0.0000
0.0323 -0.0485  0.2342 -0.0194  0.6783
1.5569
2.0656
-2.9054
-8.0282
3.4819
```

---

## Implemented Numerical Methods

### 1. Gaussian Elimination with Complete Pivoting

A direct method for solving systems of linear equations.

Unlike ordinary Gaussian elimination, this implementation uses **complete pivoting**, selecting the largest absolute element in the remaining submatrix at every elimination step.

**Implementation steps:**

1. Find the largest absolute element in the remaining submatrix.
2. Perform row and column permutations to move the selected element to the pivot position.
3. Perform forward elimination.
4. Apply back substitution.
5. Restore the original order of unknown variables using the column permutation array.

The determinant is calculated while accounting for row and column swaps:

$$\det(A)=(-1)^{s}\prod_{i=1}^{n}u_{ii}$$

where $s$ is the total number of row and column swaps, and $u_{ii}$ are the diagonal elements of the resulting upper triangular matrix.

**Additional calculations:**

- Determinant of matrix $A$.
- Inverse matrix $A^{-1}$.
- Condition number.
- Residual vector and its norm.

### 2. Left Sweep Method (Thomas Algorithm)

A direct method designed for solving tridiagonal systems of linear equations.

A tridiagonal matrix has non-zero elements only on the main diagonal and the two adjacent diagonals.

The system can be represented as:

$$a_i x_{i-1}+b_i x_i+c_i x_{i+1}=d_i$$

**Implementation steps:**

1. Check whether the coefficient matrix is tridiagonal.
2. Perform the forward sweep to calculate auxiliary coefficients.
3. Perform backward substitution to obtain the solution.

The forward sweep uses the following recurrence relations:

$$\xi_i=\frac{a_i}{b_i-c_i\xi_{i+1}}$$

$$\eta_i=\frac{d_i+c_i\eta_{i+1}}{b_i-c_i\xi_{i+1}}$$

The solution is obtained using:

$$x_{i+1}=\xi_{i+1}x_i+\eta_{i+1}$$

**Additional calculations:**

- Determinant using the tridiagonal recurrence formula.
- Inverse matrix using repeated applications of the left sweep method.
- Condition number.
- Residual matrix and residual vector.

The method is executed only if the input matrix is tridiagonal. Otherwise, it is automatically skipped.

### 3. Jacobi Iterative Method

An iterative method in which each new approximation is calculated using only the values from the previous iteration.

The iteration formula is:

$$
x_i^{(k+1)} =
\frac{1}{a_{ii}}
\left(
b_i -
\sum_{\substack{j=1,\,j\neq i}}^{n}
a_{ij}x_j^{(k)}
\right)
$$

**Parameters:**

- Initial approximation: $x^{(0)}=b$
- Required accuracy: $\varepsilon=10^{-5}$
- Maximum iterations: $N_{\max}=10000$

**Stopping criterion:**

$$\left\|x^{(k+1)}-x^{(k)}\right\|_\infty\leq\varepsilon$$

The infinity norm of a vector is defined as:

$$\|x\|_\infty=\max_i|x_i|$$

The implementation uses the iteration matrix representation:

$$x^{(k+1)}=Bx^{(k)}+g$$

where:

$$B_{ij}=
\begin{cases}
-\dfrac{a_{ij}}{a_{ii}}, & i\neq j\\
0, & i=j
\end{cases}$$

$$g_i=\frac{b_i}{a_{ii}}$$

The program calculates the final solution, number of iterations, and residual vector.

### 4. Successive Over-Relaxation (SOR) Method

An iterative method based on the Gauss-Seidel approach with an additional relaxation parameter.

The iteration formula is:

$$x_i^{(k+1)}=(1-\omega)x_i^{(k)}+\omega x_{i,GS}^{(k+1)}$$

where $x_{i,GS}^{(k+1)}$ is calculated using the most recently available values:

$$x_{i,GS}^{(k+1)}=\frac{1}{a_{ii}}\left(b_i-\sum_{j=1}^{i-1}a_{ij}x_j^{(k+1)}-\sum_{j=i+1}^{n}a_{ij}x_j^{(k)}\right)$$

**Parameters:**

- Initial approximation: $x^{(0)}=b$
- Relaxation parameter: $\omega=1.5$
- Required accuracy: $\varepsilon=10^{-5}$
- Maximum iterations: $N_{\max}=10000$

**Stopping criterion:**

$$\left\|x^{(k+1)}-x^{(k)}\right\|_\infty\leq\varepsilon$$

The program calculates the final solution, number of iterations, and residual vector.

---

## Numerical Analysis

The program performs additional calculations to evaluate the accuracy and numerical stability of the obtained results.

### 1. Matrix Determinant

The determinant of matrix $A$ is calculated using Gaussian elimination with complete pivoting.

$$\det(A)=(-1)^s\prod_{i=1}^{n}u_{ii}$$

### 2. Inverse Matrix

The inverse matrix is calculated by solving a set of linear systems:

$$AX=E$$

where $E$ is the identity matrix.

Each column of the inverse matrix is obtained by solving:

$$Ax_i=e_i$$

where $e_i$ is the corresponding column of the identity matrix.

### 3. Condition Number

The condition number is calculated using the infinity matrix norm:

$$\kappa_\infty(A)=\|A\|_\infty\cdot\|A^{-1}\|_\infty$$

The matrix infinity norm is defined as:

$$\|A\|_\infty=\max_i\sum_{j=1}^{n}|a_{ij}|$$

A larger condition number indicates that the system may be more sensitive to perturbations in the input data.

### 4. Residual Matrix

The residual matrix is calculated as:

$$R=A^{-1}A-E$$

Its infinity norm is also calculated:

$$\|R\|_\infty=\max_i\sum_{j=1}^{n}|r_{ij}|$$

This value is used to evaluate the accuracy of the calculated inverse matrix.

### 5. Residual Vector

For each obtained solution, the residual vector is calculated as:

$$r=Ax-b$$

Its infinity norm is:

$$\|r\|_\infty=\max_i|r_i|$$

A smaller residual norm indicates that the obtained solution satisfies the original system more accurately.

---

## Convergence Analysis

The convergence of the iterative methods is evaluated using the difference between two consecutive approximations.

The selected stopping criterion is:

$$\left\|x^{(k+1)}-x^{(k)}\right\|_\infty\leq 10^{-5}$$

### Jacobi Method

The Jacobi method converges if the spectral radius of its iteration matrix satisfies:

$$\rho(B_J)<1$$

A sufficient condition for convergence is strict diagonal dominance:

$$|a_{ii}|>\sum_{j\neq i}|a_{ij}|,\quad i=1,\ldots,n$$

### SOR Method

The convergence of the SOR method depends on the coefficient matrix and the relaxation parameter $\omega$.

For a symmetric positive definite matrix, a sufficient convergence condition is:

$$0<\omega<2$$

The chosen relaxation parameter is:

$$\omega=1.5$$

Both iterative methods have a maximum iteration limit of 10,000 to prevent an infinite iteration process.

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
- Determinant of matrix $A$.
- Inverse matrix $A^{-1}$.
- Condition number of matrix $A$.
- Residual matrix and its norm.
- Residual vector and its norm.
- Left sweep solution and additional calculations (if the matrix is tridiagonal).
- Jacobi method solution and iteration count.
- SOR method solution and iteration count.
- Residual vectors and their norms for iterative methods.

All numerical values are displayed in scientific notation where appropriate.

If an iterative method does not converge within the specified iteration limit or encounters a zero diagonal element, an appropriate error message is written to the output file.

---

## Results Summary

| Method | Type | Main Characteristics |
|--------|------|----------------------|
| Gaussian Elimination | Direct | Complete pivoting, determinant, inverse matrix |
| Left Sweep | Direct | Efficient solution of tridiagonal systems |
| Jacobi | Iterative | Uses values from the previous iteration |
| SOR | Iterative | Uses updated values and relaxation parameter |

**Note:** The assigned coefficient matrix is not tridiagonal. Therefore, the Left Sweep Method is automatically skipped for the provided input data.

The accuracy of the obtained solutions is evaluated using residual vectors, while the numerical properties of the coefficient matrix are analyzed using its determinant, inverse matrix, and condition number.

---

## Conclusion

This laboratory work demonstrates the implementation and comparison of four numerical methods for solving systems of linear algebraic equations.

Gaussian elimination with complete pivoting provides a direct solution and allows the calculation of the determinant and inverse matrix.

The Left Sweep Method demonstrates an efficient approach for solving tridiagonal systems.

The Jacobi and Successive Over-Relaxation methods demonstrate iterative approaches and make it possible to analyze convergence behavior and computational efficiency.

Additional numerical calculations, including the condition number, residual matrix, and residual vector, provide tools for evaluating numerical stability and solution accuracy.

The implemented methods provide a basis for comparing direct and iterative approaches to solving systems of linear algebraic equations.