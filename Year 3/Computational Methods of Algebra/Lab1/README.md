```markdown
# Lab Work: Solving Systems of Linear Algebraic Equations (Task SLAE-08)

## Overview

The program solves a system of linear algebraic equations (SLAE) of the form `Ax = b`
using several methods, performs conditioning analysis, computes residuals,
and compares the methods in terms of accuracy and efficiency.

## Implemented Methods

| # | Method | Function in code |
|---|--------|------------------|
| 1 | Gaussian elimination (full pivoting) | `gaussian` |
| 2 | Left sweep method (tridiagonal matrices) | `tridiagonalSolveLeft` |
| 3 | Jacobi method (matrix form $x = Bx + g$) | `jacobiSecond` |
| 4 | Successive Over-Relaxation (SOR) | `sor` |

Additionally implemented:

- `inverseGaussian` — inverse matrix via Gaussian elimination;
- `inverseTridiagonal` — inverse matrix via left sweep;
- `determinantTridiagonal` — determinant of a tridiagonal matrix via the recurrence formula;
- `normMatrix`, `normVector` — matrix (row-sum / $\infty$-norm) and vector ($\infty$-norm);
- `conditionNumber` — condition number $\nu(A) = \|A\| \cdot \|A^{-1}\|$;
- `residualMatrix` — residual matrix $R = A^{-1}A - E$;
- `residualVector` — residual vector $r = Ax - b$;
- `isTridiagonal` — tridiagonality check;
- `multiply`, `printVector`, `printMatrix` — helper utilities.

## Project Structure

```
.
├── main.cpp        # all source code
├── Input.txt       # input data
├── Output.txt      # results (created automatically)
└── README.md       # this file
```

## Input File Format (`Input.txt`)

```
n
a11 a12 ... a1n
a21 a22 ... a2n
...
an1 an2 ... ann
b1 b2 ... bn
```

- First line — dimension $n$.
- Next $n$ lines — matrix $A$ ($n$ numbers per line).
- Last line — right-hand side vector $b$ ($n$ numbers).

### Example ($n = 5$)

```
5
0.7914  0.0000 -0.2067  0.1454  0.2423
-0.0485 0.5168  0.0000 -0.0985  0.0323
0.0162 -0.1454  0.9367  0.0178  0.0565
0.0485  0.0000 -0.1179  0.9367  0.0000
0.0323 -0.0485  0.2342 -0.0194  0.6783
1.5569 2.0656 -2.9054 -8.0282 3.4819
```

## Output File Format (`Output.txt`)

The file contains the following sections:

1. **Gaussian Method** — solution, determinant, inverse matrix,
   condition number $\nu(A)$, residual matrix $R = A^{-1}A - E$,
   residual vector $r = Ax - b$, and their norms.
2. **Left Sweep Method (Tridiagonal)** — executed only if the matrix is tridiagonal:
   solution, determinant, inverse matrix, $\nu(A)$, residuals.
   Otherwise a skip message is printed.
3. **Jacobi Method** — solution, iteration count, residual vector and its norm.
4. **SOR Method** — solution, iteration count, residual vector and its norm.

## Criteria and Parameters

- **Stopping criterion for iterative methods:**
  $$\|x^{k+1} - x^{k}\|_\infty \le \varepsilon, \quad \varepsilon = 10^{-5}.$$
- **Initial guess:** $x^{(0)} = b$.
- **SOR relaxation parameter:** $\omega = 1.5$.
- **Maximum number of iterations:** $10000$.
- **Zero-pivot threshold:** $10^{-15}$.
- **Norms:** matrix norm — maximum row sum of absolute values ($\|\cdot\|_\infty$);
  vector norm — maximum absolute component ($\|\cdot\|_\infty$).

## Build and Run

### Linux / macOS
```bash
g++ -std=c++17 -O2 -o slae main.cpp
./slae
```

### Windows (MinGW)
```bash
g++ -std=c++17 -O2 -o slae.exe main.cpp
slae.exe
```

> **Note:** `Input.txt` must be in the working directory (next to the executable).

## Convergence Justification

- **Jacobi method** converges if $A$ is strictly diagonally dominant, i.e.
  $$|a_{ii}| > \sum_{j \ne i} |a_{ij}| \quad \forall i,$$
  or if the spectral radius of the iteration matrix $B$ satisfies $\rho(B) < 1$.
- **SOR method** converges for $0 < \omega < 2$ when $A$ is symmetric positive definite;
  for $1 < \omega < 2$ it accelerates convergence compared to Gauss–Seidel
  ($\omega = 1$ reduces SOR to Gauss–Seidel). The program uses $\omega = 1.5$.

If the convergence conditions are not met or the iteration count exceeds $10000$,
the program reports a convergence failure.

## Method Comparison

| Method | Accuracy | Efficiency |
|--------|----------|------------|
| Gaussian (full pivoting) | high, stable | $O(n^3)$, direct method |
| Left sweep | high | $O(n)$ for tridiagonal matrices |
| Jacobi | depends on convergence | simple iteration, $O(n^2)$ per step |
| SOR | depends on $\omega$ | usually faster than Jacobi for $1 < \omega < 2$ |

For a tridiagonal matrix, the left sweep provides a significant gain
in operation count ($O(n)$ versus $O(n^3)$ for Gaussian elimination).

## Notes

- The inverse matrix in Gaussian elimination is computed by solving $n$ systems
  $Ax = e_j$ for the unit vectors $e_j$ (column by column).
- The determinant is accumulated with regard to row/column permutations
  (each swap flips the sign).
- The left sweep uses a backward pass with coefficients $\xi_i$, $\eta_i$;
  if a zero pivot is encountered, the method returns `ok = false`.
- All numerical results are printed in scientific notation (`std::scientific`)
  with field width 16, except the determinant and norms (`std::defaultfloat`).
```