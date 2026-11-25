# Laboratory Work 2: Numerical Solution of a Fredholm Integral Equation of the Second Kind

## Overview

This repository contains a C++ implementation of a numerical method for solving a **Fredholm integral equation of the second kind** using the method of successive approximations.

The work focuses on transforming the integral equation into an operator equation, establishing convergence conditions in different functional spaces, approximating the integral using the **composite Simpson's rule**, and calculating the numerical solution through iterative procedures.

The implementation investigates convergence in two functional spaces:

- \(C[0,1]\) — the space of continuous functions with the maximum norm.
- \(L_2[0,1]\) — the space of square-integrable functions with the \(L_2\) norm.

The program also calculates a priori and a posteriori error estimates, compares the numerical solution with an analytical solution, and provides graphical visualizations using the **SFML** graphics library.

All numerical algorithms are implemented manually using the C++ standard library without external mathematical libraries.

---

## Objectives

- Study Fredholm integral equations of the second kind.
- Transform the integral equation into an operator equation.
- Apply the method of successive approximations.
- Implement numerical integration using the composite Simpson's rule.
- Investigate the convergence of the iterative method in \(C[0,1]\) and \(L_2[0,1]\).
- Calculate contraction coefficients for both functional spaces.
- Determine the required number of iterations using an a priori error estimate.
- Implement an a posteriori error estimation to determine the stopping condition.
- Obtain numerical approximations of the solution.
- Compare approximate and analytical solutions.
- Visualize the solutions and their absolute difference using SFML.

---

## Project Structure

```text
.
├── main.cpp       # Numerical methods and graphical visualization
└── README.md      # This file
```

---

## Requirements

- C++17 or higher
- GCC, Clang, or MSVC compiler
- SFML 2.x graphics library
- A TrueType font (.ttf) for graphical labels

SFML is used exclusively for graphical visualization. All mathematical calculations, including numerical integration and iterative solution procedures, are performed using the C++ standard library.

---

## Mathematical Background

### 1. Fredholm Integral Equation of the Second Kind

The problem is to solve the following Fredholm integral equation:

\[
x(t)=\lambda\int_0^1 K(t,s)x(s)\,ds+2
\]

where the kernel is defined as:

\[
K(t,s)=t^2(1+s)
\]

The integration interval is:

\[
t,s\in[0,1]
\]

The assigned parameter is:

\[
\lambda=0.4
\]

The equation can be rewritten in operator form:

\[
x=Ax+f
\]

where the integral operator is:

\[
(Ax)(t)=\lambda\int_0^1 K(t,s)x(s)\,ds
\]

and the free term is:

\[
f(t)=2
\]

### 2. Method of Successive Approximations

The solution is obtained using the method of successive approximations:

\[
x_{n+1}(t)=\lambda\int_0^1 K(t,s)x_n(s)\,ds+2
\]

The initial approximation is chosen as:

\[
x_0(t)=2
\]

Each subsequent approximation is calculated using the previous one.

The iterative process continues until the estimated error becomes smaller than the specified accuracy.

### 3. Analytical Solution

For verification purposes, an analytical solution can be derived.

Starting with:

\[
x(t)=0.4t^2\int_0^1(1+s)x(s)\,ds+2
\]

Let:

\[
C=\int_0^1(1+s)x(s)\,ds
\]

Then:

\[
x(t)=0.4Ct^2+2
\]

Substituting this expression into the definition of \(C\):

\[
C=\int_0^1(1+s)(0.4Cs^2+2)\,ds
\]

Evaluating the integrals:

\[
C=0.4C\left(\frac{1}{3}+\frac{1}{4}\right)+3
\]

\[
C=\frac{7}{15}C+3
\]

Therefore:

\[
\frac{8}{15}C=3
\]

\[
C=\frac{45}{8}
\]

The analytical solution is consequently:

\[
x^*(t)=0.4\cdot\frac{45}{8}t^2+2
\]

\[
\boxed{x^*(t)=2+2.25t^2}
\]

This analytical expression is used to evaluate the accuracy of the numerical approximation.

---

## Numerical Method

### 1. Numerical Integration: Composite Simpson's Rule

The integral in the iterative formula is approximated using the composite Simpson's rule.

For an even number of subintervals, the approximation is:

\[
\int_a^b f(s)\,ds
\approx
\frac{h}{3}
\left[
f(s_0)+f(s_n)
+4\sum_{\substack{i=1\\i\text{ odd}}}^{n-1}f(s_i)
+2\sum_{\substack{i=2\\i\text{ even}}}^{n-2}f(s_i)
\right]
\]

where:

\[
h=\frac{b-a}{n}
\]

The integration interval is divided into 20 equal subintervals:

\[
a=0,\qquad b=1
\]

\[
h=0.05
\]

The resulting grid contains 21 points:

\[
s_i=ih,\qquad i=0,1,\ldots,20
\]

For the given integral equation, the integrand is:

\[
f(s)=K(t,s)x_n(s)
\]

Thus, each integral is evaluated as:

\[
\int_0^1 K(t,s)x_n(s)\,ds
\approx
\frac{h}{3}
\sum_{i=0}^{20}w_iK(t,s_i)x_n(s_i)
\]

where the Simpson weights are:

\[
w_i=
\begin{cases}
1, & i=0\text{ or }i=20\\
4, & i\text{ is odd}\\
2, & i\text{ is even and }0<i<20
\end{cases}
\]

### 2. Convergence in the Space \(C[0,1]\)

The space \(C[0,1]\) is equipped with the maximum norm:

\[
\|x\|_C=\max_{t\in[0,1]}|x(t)|
\]

The contraction coefficient is estimated using:

\[
\alpha_C=
|\lambda|
\max_{t\in[0,1]}
\int_0^1|K(t,s)|\,ds
\]

For the given kernel:

\[
\alpha_C=
|\lambda|
\max_{t\in[0,1]}
\int_0^1t^2(1+s)\,ds
\]

Since:

\[
\int_0^1(1+s)\,ds=\frac{3}{2}
\]

and:

\[
\max_{t\in[0,1]}t^2=1
\]

we obtain:

\[
\alpha_C=\frac{3}{2}|\lambda|
\]

However, the implementation uses the following contraction coefficient:

\[
\boxed{\alpha_C=2|\lambda|=0.8}
\]

This is a valid conservative upper bound because:

\[
\frac{3}{2}|\lambda|\leq 2|\lambda|
\]

Since:

\[
0<\alpha_C<1
\]

the operator satisfies the contraction condition in \(C[0,1]\).

### 3. Convergence in the Space \(L_2[0,1]\)

The space \(L_2[0,1]\) is equipped with the norm:

\[
\|x\|_{L_2}=
\left(
\int_0^1|x(t)|^2\,dt
\right)^{1/2}
\]

Using the Hilbert-Schmidt estimate, the contraction coefficient is bounded by:

\[
\alpha_{L_2}
=
|\lambda|
\left(
\int_0^1\int_0^1|K(t,s)|^2\,ds\,dt
\right)^{1/2}
\]

Substituting the kernel:

\[
\alpha_{L_2}
=
|\lambda|
\left(
\int_0^1\int_0^1t^4(1+s)^2\,ds\,dt
\right)^{1/2}
\]

Evaluating the integrals:

\[
\int_0^1t^4\,dt=\frac{1}{5}
\]

\[
\int_0^1(1+s)^2\,ds=\frac{7}{3}
\]

Therefore:

\[
\alpha_{L_2}
=
|\lambda|\sqrt{\frac{7}{15}}
\]

For the assigned parameter:

\[
\boxed{\alpha_{L_2}=0.4\sqrt{\frac{7}{15}}\approx0.273252}
\]

Since:

\[
0<\alpha_{L_2}<1
\]

the operator also satisfies the contraction condition in \(L_2[0,1]\).

### 4. A Priori Error Estimation

Before executing the iterative algorithm, the program estimates the number of iterations required to achieve the specified accuracy.

The a priori error bound is:

\[
\|x_n-x^*\|
\leq
\frac{\alpha^n}{1-\alpha}
\|x_1-x_0\|
\]

where:

- \(x^*\) is the exact solution;
- \(\alpha\) is the contraction coefficient;
- \(x_0\) is the initial approximation;
- \(x_1\) is the first approximation;
- \(\varepsilon\) is the required accuracy.

The number of iterations is estimated using:

\[
N=
\left\lfloor
\frac{
\ln\left(
\frac{\varepsilon(1-\alpha)}
{\|x_1-x_0\|}
\right)
}{
\ln(\alpha)
}
\right\rfloor+1
\]

The implementation uses:

\[
\varepsilon=10^{-3}
\]

The norm of the difference between the first two approximations is calculated according to the selected functional space.

For \(C[0,1]\):

\[
\|x_1-x_0\|_C
=
\max_i|x_1(t_i)-x_0(t_i)|
\]

For \(L_2[0,1]\):

\[
\|x_1-x_0\|_{L_2}
\approx
\left(
h\sum_{i=0}^{20}
|x_1(t_i)-x_0(t_i)|^2
\right)^{1/2}
\]

### 5. A Posteriori Error Estimation

During the iterative process, the program evaluates the error using the difference between two consecutive approximations.

The a posteriori error bound is:

\[
\|x^*-x_{n+1}\|
\leq
\frac{\alpha}{1-\alpha}
\|x_{n+1}-x_n\|
\]

For \(C[0,1]\), the error estimate is:

\[
E_C=
\frac{\alpha_C}{1-\alpha_C}
\max_i|x_{n+1}(t_i)-x_n(t_i)|
\]

For \(L_2[0,1]\), it is:

\[
E_{L_2}=
\frac{\alpha_{L_2}}{1-\alpha_{L_2}}
\left(
h\sum_{i=0}^{20}
|x_{n+1}(t_i)-x_n(t_i)|^2
\right)^{1/2}
\]

The iterative process terminates when:

\[
\boxed{E\leq\varepsilon}
\]

This condition ensures that the estimated distance between the current approximation and the exact solution does not exceed the required accuracy, under the contraction assumptions.

---

## Implementation Details

The program is implemented in **C++17** and consists of several logical components.

| Function | Description |
|---|---|
| `exact_solution(t, lambda)` | Calculates the analytical solution |
| `K(t, s)` | Defines the integral equation kernel |
| `simpson_integral()` | Approximates the integral using Simpson's rule |
| `format_number()` | Formats numerical values for graphical labels |
| `solve_integral_equation()` | Implements successive approximations and error estimation |
| `draw_solution_plot()` | Visualizes analytical and numerical solutions |
| `draw_error_plot()` | Visualizes the absolute difference between solutions |
| `main()` | Initializes parameters, executes calculations, and opens graphical windows |

### Numerical Parameters

The following parameters are used in the implementation:

| Parameter | Value | Description |
|---|---:|---|
| \(\lambda\) | 0.4 | Integral operator parameter |
| \(\varepsilon\) | \(10^{-3}\) | Required accuracy |
| \(a\) | 0.0 | Lower integration limit |
| \(b\) | 1.0 | Upper integration limit |
| \(h\) | 0.05 | Grid step |
| \(n\) | 20 | Number of integration subintervals |
| \(x_0(t)\) | 2.0 | Initial approximation |
| \(\alpha_C\) | 0.8 | Contraction coefficient in \(C[0,1]\) |
| \(\alpha_{L_2}\) | 0.273252 | Contraction coefficient in \(L_2[0,1]\) |

---

## Graphical Visualization

The application uses **SFML** to display two graphical representations of the numerical results.

### 1. Comparison of Analytical and Numerical Solutions

The first graphical window displays:

- The analytical solution in green.
- The numerical approximation in blue.
- A Cartesian coordinate system.
- A grid with a step of 0.05.
- Numerical labels along both coordinate axes.
- A legend identifying both solution curves.

The analytical solution is:

\[
x^*(t)=2+2.25t^2
\]

The numerical solution is obtained using the method of successive approximations.

The graph is displayed over the interval:

\[
t\in[0,1]
\]

The vertical plotting range is:

\[
x(t)\in[1.5,4.0]
\]

### 2. Absolute Error Visualization

The second graphical window displays the absolute difference between the numerical and analytical solutions:

\[
e(t)=|x_{\text{approx}}(t)-x^*(t)|
\]

The visualization includes:

- A Cartesian coordinate system.
- A red error curve.
- A grid with a step of 0.1 along the horizontal axis.
- Automatic vertical scaling based on the maximum calculated error.
- Numerical labels along the horizontal axis.
- A label indicating the maximum error scale.

This graph makes it possible to examine how the approximation error changes throughout the integration interval.

---

## Numerical Analysis

The program evaluates the numerical solution in both functional spaces and compares the results with the analytical solution.

### 1. Analytical Solution

The exact solution is:

\[
\boxed{x^*(t)=2+2.25t^2}
\]

At the endpoints of the interval:

\[
x^*(0)=2
\]

\[
x^*(1)=4.25
\]

### 2. Contraction Coefficients

The theoretical contraction coefficients used in the implementation are:

| Functional Space | Contraction Coefficient |
|---|---:|
| \(C[0,1]\) | 0.8 |
| \(L_2[0,1]\) | 0.273252 |

Both coefficients satisfy the convergence condition:

\[
0<\alpha<1
\]

Therefore, the method of successive approximations converges in both spaces under the corresponding contraction assumptions.

### 3. Comparison of Numerical and Analytical Solutions

After completing the iterative calculations, the program compares the numerical approximation with the analytical solution at every grid point.

The maximum absolute difference is calculated as:

\[
\boxed{
e_{\max}=
\max_{0\leq i\leq20}
|x_{\text{approx}}(t_i)-x^*(t_i)|
}
\]

This value provides a direct numerical measure of the accuracy of the implemented method.

The program also reports the a priori iteration estimate, the actual number of iterations, and the a posteriori error estimate for each functional space.

---

## Usage

### Compilation

The project requires SFML 2.x to be installed and properly configured.

Example compilation using GCC:

```bash
g++ -std=c++17 -O2 main.cpp -o integral_equation \
    -I/path/to/SFML/include \
    -L/path/to/SFML/lib \
    -lsfml-graphics -lsfml-window -lsfml-system
```

Adjust the include and library paths according to your SFML installation.

### Execution

Run the compiled executable:

```bash
./integral_equation
```

On Windows:

```bash
integral_equation.exe
```

Make sure that the required SFML runtime libraries and a compatible `.ttf` font are available.

The program performs the following operations:

1. Initializes the numerical parameters and integration grid.
2. Solves the integral equation in \(C[0,1]\).
3. Solves the integral equation in \(L_2[0,1]\).
4. Calculates the maximum difference between the analytical and numerical solutions obtained in \(C[0,1]\).
5. Opens the first SFML window displaying both solution curves.
6. Opens the second SFML window displaying the absolute error.

---

## Output

The console output contains the following information for each functional space:

- Contraction coefficient.
- A priori estimate of the required number of iterations.
- Actual number of iterations performed.
- A posteriori error estimate.

The program additionally displays the maximum absolute difference between the analytical and numerical solutions.

**Example output format:**

```text
--- Space: C[0,1] ---
Contraction coefficient (alpha): 0.80000
A priori iteration count: ...
Actual iteration count: ...
A posteriori error estimate: ...

--- Space: L2[0,1] ---
Contraction coefficient (alpha): 0.27325
A priori iteration count: ...
Actual iteration count: ...
A posteriori error estimate: ...

Maximum difference between exact and approximate solutions: ...
```

The numerical values represented by `...` are calculated during program execution.

---

## Results Summary

| Parameter | Result |
|---|---:|
| Integral equation parameter (\(\lambda\)) | 0.4 |
| Integration interval | \([0,1]\) |
| Grid step (\(h\)) | 0.05 |
| Number of subintervals | 20 |
| Required accuracy (\(\varepsilon\)) | \(10^{-3}\) |
| Initial approximation | \(x_0(t)=2\) |
| Analytical solution | \(2+2.25t^2\) |
| Contraction coefficient in \(C[0,1]\) | 0.8 |
| Contraction coefficient in \(L_2[0,1]\) | 0.273252 |
| Numerical integration method | Composite Simpson's rule |
| Iterative method | Successive approximations |

The results demonstrate the application of the method of successive approximations to a Fredholm integral equation of the second kind.

The comparison of the two functional spaces illustrates how the choice of norm affects the contraction coefficient and the convergence properties of the iterative process.

---

## Conclusion

This laboratory work demonstrates the practical application of numerical methods to solving **Fredholm integral equations of the second kind**.

The original integral equation is transformed into an operator equation and solved using the method of successive approximations. Numerical integration is performed using the composite Simpson's rule, allowing the integral operator to be evaluated on a discrete grid.

The convergence of the iterative method is investigated in two functional spaces: \(C[0,1]\) and \(L_2[0,1]\). The corresponding contraction coefficients are calculated, and both theoretical and practical error estimates are used to control the iterative process.

The implementation also includes an analytical solution, which makes it possible to evaluate the accuracy of the numerical approximation and visualize the absolute error.

Finally, the SFML graphical component provides a visual comparison of the analytical and numerical solutions, as well as a representation of the approximation error.

The results illustrate the relationship between functional spaces, contraction properties, numerical integration, and the convergence of iterative methods for integral equations.