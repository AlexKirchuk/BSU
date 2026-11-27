# Computational Methods of Algebra — Lab Work Collection

This repository contains a comprehensive collection of **Computational Methods of Algebra** laboratory works, implemented in **C++** with a strong emphasis on **numerical accuracy**, **algorithmic rigor**, and **error analysis**.

The projects focus on the practical implementation of direct and iterative numerical algorithms for **solving systems of linear algebraic equations (SLAE)** and **solving complete and partial eigenvalue problems (EVP)**, alongside matrix conditioning, residual verification, and convergence analysis.

All numerical algorithms are implemented from scratch using the **C++ standard library** without external mathematical or linear algebra solvers.

---

## Overview

- Total of **2 laboratory works** covering linear algebraic systems and matrix eigenvalue problems
- All laboratory works are implemented as **independent, self-contained C++ projects**
- Each assignment bridges **theoretical numerical linear algebra** with **clean, reproducible C++ computation**
- Includes comprehensive **residual verification**, **matrix conditioning evaluation**, and **comparative method analysis**

The repository reflects a **progressive computational path**, starting from direct and iterative solvers for linear systems $Ax = b$ and advancing to spectral methods for characteristic polynomials, full spectra, and extremal eigenpairs of symmetric positive-definite matrices $M = A^T A$.

---

## Development Environment

- **Language standard**: C++17 or higher
- **Compilers**: GCC, Clang, or MSVC
- **IDE**:
  - **Microsoft Visual Studio 2026** — C++ development and debugging
- **Core libraries**:
  - C++ Standard Library (`<vector>`, `<cmath>`, `<iomanip>`, `<fstream>`, `<limits>`) — manual implementation of all numerical methods

---

## Laboratory Works

### **Lab 1 — Numerical Methods for Solving Systems of Linear Algebraic Equations**
- Direct and iterative solution of linear systems of the form:
  $$Ax = b$$
- Implementation of **Gaussian elimination with complete pivoting** (including matrix determinant calculation and matrix inversion $A^{-1}$)
- Implementation of the **Left Sweep Method (Thomas Algorithm)** for tridiagonal systems with automatic structural verification
- Implementation of the **Jacobi iterative method** and **Successive Over-Relaxation (SOR)** method ($\omega = 1.5$, $\varepsilon = 10^{-5}$)
- Calculation of the matrix **condition number** $\kappa_{\mathrm{I}}(A) = \|A\|_{\mathrm{I}} \cdot \|A^{-1}\|_{\mathrm{I}}$
- Accuracy evaluation via residual vectors ($r = Ax - b$) and residual matrices ($R = A^{-1}A - E$) in the cubic norm $\|\cdot\|_{\mathrm{I}}$

---

### **Lab 2 — Numerical Methods for Solving the Eigenvalue Problem**
- Spectral analysis of the symmetric positive-definite matrix $M = A^T A$:
  $$Mx = \lambda x$$
- Construction of the characteristic polynomial $P_n(\lambda) = \lambda^n - p_1\lambda^{n-1} - \dots - p_n$ via the **Krylov Method**
- Complete spectral decomposition ($\lambda_i, x_i$, $i = \overline{1,n}$) using the **Iterative Jacobi Rotation Method** ($\varepsilon = 10^{-5}$)
- Similarity reduction to Frobenius normal form and eigenvector reconstruction via **Danilevsky's Method**, benchmarked against the Jacobi rotation eigenvectors
- Determination of the minimal eigenvalue $\lambda_{\min}$ and its corresponding eigenvector using the **Power Method (Inverse Iteration)** ($\varepsilon = 10^{-5}$)
- Eigenvector normalization by the last coordinate ($x_n = 1$) and accuracy evaluation via polynomial residuals $\varphi_i = P_n(\lambda_i)$ and vector residuals $r_i = Mx_i - \lambda_i x_i$ in the cubic norm $\|\cdot\|_{\mathrm{I}}$

---

## Key Concepts Covered

- Direct SLAE solvers (Gaussian elimination with complete pivoting, Thomas algorithm)
- Stationary iterative methods (Jacobi, Gauss–Seidel, Successive Over-Relaxation)
- Matrix norms ($\|\cdot\|_{\mathrm{I}}$), condition numbers, and numerical stability
- Cayley–Hamilton theorem and Krylov subspaces
- Similarity transformations and Frobenius normal form (Danilevsky's method)
- Orthogonal transformations and Jacobi eigenvalue algorithm
- Inverse iteration power method and Rayleigh-type quotients
- Residual analysis and comparative evaluation of accuracy and computational complexity

---

## Purpose of This Repository

This repository serves as:

- A **complete reference** for fundamental algorithms in Computational Methods of Algebra
- A demonstration of **clean, dependency-free numerical C++ programming**
- A structured collection of **academic laboratory works** with full mathematical documentation
- A practical bridge between **linear algebra theory** and **scientific computing**

---

## License

Educational projects developed as part of the **Computational Methods of Algebra** course.