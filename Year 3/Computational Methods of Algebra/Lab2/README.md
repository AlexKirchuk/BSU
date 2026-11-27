# Laboratory Work 2: Numerical Methods for Solving the Eigenvalue Problem

## Overview

This repository contains the implementation of a laboratory work on numerical methods for solving the eigenvalue problem (EVP) for symmetric positive-definite matrices.

Given a real matrix $A$ of size $n \times n$, the work focuses on finding eigenvalues $\lambda_i$ and corresponding eigenvectors $x_i$ of the symmetric matrix $M = A^T A$:

$$M x = \lambda x, \quad M = A^T A$$

using direct and iterative numerical methods, normalizing eigenvectors by their last coordinate, and evaluating solution accuracy via polynomial and vector residuals.

The implementation is written in **C++** using the standard library. All numerical algorithms are implemented manually without external mathematical libraries.

---

## Objectives

- Construct the symmetric positive-definite matrix $M = A^T A$ from the input matrix $A$.
- Implement the **Krylov Method** to find the coefficients $p_1, \dots, p_n$ of the characteristic polynomial $P_n(\lambda)$.
- Implement the **Iterative Jacobi Rotation Method** to find the complete spectrum $\{\lambda_i, i = \overline{1,n}\}$ and orthonormal eigenvectors $\{x_i, i = \overline{1,n}\}$ of $A^T A$.
- Implement **Danilevsky's Method** (reduction to Frobenius normal form) to compute eigenvectors using the eigenvalues obtained by the rotation method, and compare them with the rotation method eigenvectors.
- Implement the **Power Method (Inverse Iteration)** to find the minimal eigenvalue $\lambda_{\min}$ and its corresponding eigenvector.
- Normalize all obtained eigenvectors by their last coordinate ($x_n = 1$).
- Evaluate accuracy by computing characteristic polynomial residuals $\varphi_i = P_n(\lambda_i)$ and eigenvector residuals $r_i = A^T A x_i - \lambda_i x_i$ in the cubic norm $\Vert{}\cdot\Vert{}_{\mathrm{I}}$.
- Compare the implemented methods in terms of accuracy and computational efficiency.

---

## Project Structure

```text
.
├── main.cpp       # Implementation of all numerical methods
├── Input.txt      # Input matrix dimension n and matrix A
├── Output.txt     # Calculation results, eigenvectors, and residuals
└── README.md      # This file

```

---

## Requirements

* C++17 or higher
* GCC, Clang, or MSVC compiler
* Standard C++ library

No external libraries are required.

---

## Input Data

The program reads input data from `Input.txt`.

The input format consists of:

1. Matrix dimension $n$.
2. Real matrix $A$ of size $n \times n$.

**Parameters (Assigned Variant № ПСЗ-08):**

| Parameter | Value | Description |
| --- | --- | --- |
| $n$ | 5 | Matrix dimension |
| $\varepsilon$ | $10^{-5}$ | Required accuracy for iterative methods |
| $c^{(0)}$ | $(1, 0, \dots, 0)^T$ | Initial vector for the Krylov method |
| $z^{(0)}$ | $(1, 1, \dots, 1)^T$ | Initial vector for the Power method (normalized) |
| $N_{\max}$ | 10000 | Maximum number of iterations |
| $\delta$ | $10^{-15}$ | Zero pivot / division threshold |

**Input format (`Input.txt`):**

```text
5
0.7914  0.0000 -0.2067  0.1454  0.2423
-0.0485 0.5168  0.0000 -0.0985  0.0323
0.0162 -0.1454  0.9367  0.0178  0.0565
0.0485  0.0000 -0.1179  0.9367  0.0000
0.0323 -0.0485  0.2342 -0.0194  0.6783

```

---

## Implemented Numerical Methods

### 1. Krylov Method (Characteristic Polynomial)

A direct method based on the Cayley–Hamilton theorem for constructing the characteristic polynomial:

$$P_n(\lambda) = \lambda^n - p_1 \lambda^{n-1} - p_2 \lambda^{n-2} - \dots - p_{n-1}\lambda - p_n$$

**Implementation steps:**

1. Choose an initial non-zero vector $c^0 = (1, 0, \dots, 0)^T$.
2. Generate the Krylov sequence of vectors:

$$c^k = M c^{k-1}, \quad k = \overline{1,n}$$

3. Form the system of linear equations:

$$p_1 c^{n-1} + p_2 c^{n-2} + \dots + p_n c^0 = c^n$$

4. Solve the system using **Gaussian elimination with complete pivoting** to obtain the polynomial coefficients $p_1, \dots, p_n$.

### 2. Iterative Jacobi Rotation Method

An iterative method for solving the complete eigenvalue problem for a real symmetric matrix $M = M^T$ via a sequence of orthogonal similarity transformations:

$$A^{k+1} = (T_{pq}^k)^T A^k T_{pq}^k, \quad U^{k+1} = U^k T_{pq}^k, \quad A^0 = M, \quad U^0 = E$$

**Implementation steps:**

1. Find the largest off-diagonal element in absolute value $a_{pq}^k$ ($p < q$) in the upper triangle.
2. Compute the rotation angle $\varphi^k$ ($|\varphi^k| \le \frac{\pi}{4}$) to annihilate $a_{pq}^{k+1}$:

$$\operatorname{tg} 2\varphi^k = \frac{2a_{pq}^k}{a_{pp}^k - a_{qq}^k}, \quad \cos 2\varphi^k = \frac{1}{\sqrt{1 + \operatorname{tg}^2 2\varphi^k}}$$

$$\cos \varphi^k = \sqrt{\frac{1 + \cos 2\varphi^k}{2}}, \quad \sin \varphi^k = \operatorname{sign}\!\left(a_{pq}^k(a_{pp}^k - a_{qq}^k)\right)\sqrt{\frac{1 - \cos 2\varphi^k}{2}}$$

3. Update the matrix $A^k$ and accumulate the eigenvectors in the columns of $U^k$.
4. Repeat until the sum of squares of off-diagonal elements satisfies the stopping criterion.
5. Extract the diagonal elements as eigenvalues $\lambda_i$ and normalize each column of $U$ by its last coordinate.

**Stopping criterion:**

$$t(A^{k+1}) = \sum_{\substack{i,j=1 \\ i \ne j}}^{n} \left(a_{ij}^{k+1}\right)^2 \le \varepsilon$$

### 3. Danilevsky's Method (Eigenvector Computation)

A direct method that reduces matrix $M$ to Frobenius normal form $\Phi$ via similarity transformations:

$$\Phi = S^{-1} M S = \begin{pmatrix}
p_1 & p_2 & \dots & p_{n-1} & p_n \\
1 & 0 & \dots & 0 & 0 \\
\vdots & \vdots & \ddots & \vdots & \vdots \\
0 & 0 & \dots & 1 & 0
\end{pmatrix}$$

**Implementation steps:**

1. Sequentially transform rows $k = n, n-1, \dots, 2$ into Frobenius rows using similarity matrices $M_{k-1}^{-1} A M_{k-1}$ (performing row and column swaps if a subdiagonal pivot is zero).
2. Accumulate the transformation matrix $S = M_{n-1} \dots M_1$.
3. Verify the characteristic polynomial coefficients $p_1, \dots, p_n$ from the first row of $\Phi$.
4. For each eigenvalue $\lambda_i$ obtained from the Jacobi rotation method, construct the eigenvector in the Frobenius basis:

$$y^{(i)} = \left(\lambda_i^{n-1}, \lambda_i^{n-2}, \dots, \lambda_i, 1\right)^T$$

5. Recover the eigenvector of $M$ via $x_i = S y^{(i)}$, normalize it by its last coordinate, and compute the difference norm $\lVert x_i^{(\text{Dan})} - x_i^{(\text{Jac})} \rVert_{\mathrm{I}}$.

### 4. Power Method (Inverse Iteration for Minimal Eigenvalue)

An iterative method for solving the partial eigenvalue problem to find the smallest eigenvalue $\lambda_{\min}$ and its corresponding eigenvector.

**Implementation steps:**

1. Initialize $z^{(0)} = (1, 1, \dots, 1)^T$ and normalize it using the cubic norm: $z^{(0)} \leftarrow z^{(0)} / \lVert z^{(0)} \rVert_{\mathrm{I}}$.
2. At each iteration $k$, solve the linear system:

$$M y^{(k+1)} = z^{(k)}$$

using **Gaussian elimination with complete pivoting**.
3. Estimate the minimal eigenvalue using the Rayleigh-type quotient for symmetric matrices:

$$\lambda_{\min}^{(k+1)} = \frac{(y^{(k+1)}, z^{(k)})}{(y^{(k+1)}, y^{(k+1)})}$$

4. Normalize $z^{(k+1)} = y^{(k+1)} / \lVert y^{(k+1)} \rVert_{\mathrm{I}}$.
5. Repeat until the stopping criterion is met, then normalize the resulting eigenvector by its last coordinate.

**Stopping criterion:**

$$\left|\lambda_{\min}^{(k+1)} - \lambda_{\min}^{(k)}\right| \le \varepsilon$$

---

## Numerical Analysis

The program evaluates the accuracy and consistency of the computed eigenvalues and eigenvectors using the cubic vector norm:

$$\|v\|_{\mathrm{I}} = \max_{1 \le i \le n} |v_i|$$

### 1. Characteristic Polynomial Residual

For each computed eigenvalue $\lambda_i$, the polynomial residual is evaluated using the coefficients $p_1, \dots, p_n$ obtained from the Krylov method:

$$\varphi_i = P_n(\lambda_i) = \lambda_i^n - p_1 \lambda_i^{n-1} - \dots - p_{n-1}\lambda_i - p_n$$

### 2. Eigenvector Residual

For each eigenpair $(\lambda_i, x_i)$, the residual vector and its cubic norm are computed as:

$$r_i = M x_i - \lambda_i x_i, \quad \|r_i\|_{\mathrm{I}} = \max_{1 \le j \le n} |(r_i)_j|$$

### 3. Eigenvector Comparison (Jacobi vs. Danilevsky)

To compare the direct and iterative approaches for finding eigenvectors, the program computes the cubic norm of the difference between the normalized eigenvectors:

$$\left\|x_i^{(\text{Dan})} - x_i^{(\text{Jac})}\right\|_{\mathrm{I}}$$

---

## Convergence Analysis

* **Jacobi Rotation Method:** For a real symmetric matrix $M = A^T A$, the off-diagonal sum of squares $t(A^k)$ decreases strictly monotonically at each step according to:

$$t(A^{k+1}) = t(A^k) - 2\left(a_{pq}^k\right)^2 \le \left(1 - \frac{2}{n(n-1)}\right) t(A^k)$$

With $\varepsilon = 10^{-5}$, the process converges in **17 iterations**.

* **Power Method (Inverse Iteration):** Because $M = A^T A$ is symmetric, using the scalar product ratio accelerates convergence to $O\!\left(\left|\frac{\lambda_{\min}}{\lambda_{n-1}}\right|^{2k}\right)$. With $\varepsilon = 10^{-5}$, the method converges to $\lambda_{\min} \approx 0.230537$ in **14 iterations**.

---

## Usage

### Compilation

Using GCC:

```bash
g++ -std=c++17 -O2 main.cpp -o evp

```

### Execution

Make sure `Input.txt` is located in the working directory of the executable.

Run the program:

```bash
./evp

```

On Windows:

```bash
evp.exe

```

The program reads matrix $A$ from `Input.txt` and writes all calculation results to `Output.txt`.

---

## Output

The `Output.txt` file contains:

* Constructed symmetric matrix $M = A^T A$.
* Coefficients $p_1, \dots, p_n$ of the characteristic polynomial $P_n(\lambda)$ obtained via the Krylov method.
* Convergence status, iteration count, eigenvalues $\lambda_i$, and normalized eigenvectors $x_i$ from the Jacobi rotation method.
* Characteristic polynomial coefficients and normalized eigenvectors from Danilevsky's method, along with the difference norms $\lVert x_i^{(\text{Dan})} - x_i^{(\text{Jac})} \rVert_{\mathrm{I}}$.
* Convergence status, iteration count, minimal eigenvalue $\lambda_{\min}$, and normalized eigenvector $x_{\min}$ from the Power method.
* Polynomial residuals $\varphi_i = P_n(\lambda_i)$, residual vectors $r_i = M x_i - \lambda_i x_i$, and their cubic norms $\lVert r_i \rVert_{\mathrm{I}}$.

---

## Results Summary

| Method | Problem Type | Complexity | Iterations ($\varepsilon = 10^{-5}$) | Main Characteristics |
| --- | --- | --- | --- | --- |
| Krylov Method | Characteristic polynomial | $O(n^3)$ | Direct | Finds $p_1, \dots, p_n$ via Krylov subspace and SLAE |
| Jacobi Rotation | Complete EVP | $O(n^2)$ per step | 17 | Orthogonal similarity; high stability and accuracy |
| Danilevsky's Method | Characteristic polynomial & eigenvectors | $O(n^3)$ | Direct | Frobenius reduction; sensitive to $\lambda_i$ error in $y^{(i)}$ |
| Power Method (Inverse) | Partial EVP ($\lambda_{\min}$) | $O(n^3)$ + $O(n^2)$ per step | 14 | Finds extreme eigenvalue and eigenvector efficiently |

**Key Observations:**

* The polynomial coefficients $p_1, \dots, p_5$ computed by the Krylov and Danilevsky methods match to 10 significant digits.
* Polynomial residuals $\varphi_i = P_5(\lambda_i)$ are on the order of $10^{-9} \div 10^{-6}$, while eigenvector residuals $\lVert r_i \rVert_{\mathrm{I}}$ are on the order of $10^{-4} \div 10^{-3}$ due to vector normalization by the last coordinate and finite iteration tolerance $\varepsilon = 10^{-5}$.
* Danilevsky's eigenvector reconstruction exhibits larger deviations from the Jacobi rotation eigenvectors when eigenvector components are large or when $\lambda_i$ has approximation error, as powers $\lambda_i^k$ amplify perturbations.

---

## Conclusion

This laboratory work demonstrates the implementation and comparative analysis of four numerical methods for solving the complete and partial eigenvalue problems for the symmetric positive-definite matrix $M = A^T A$.

The Krylov and Danilevsky methods both determine the exact coefficients of the characteristic polynomial in $O(n^3)$ operations, while the iterative Jacobi rotation method reliably computes the full spectrum and an orthogonal eigenvector basis. For finding only the minimal eigenvalue $\lambda_{\min}$, the inverse iteration power method proves to be efficient and accurate. Evaluating both polynomial residuals $\varphi_i$ and vector residuals $\lVert r_i \rVert_{\mathrm{I}}$ provides a clear assessment of numerical stability and approximation accuracy across methods.