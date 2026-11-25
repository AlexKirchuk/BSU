# Laboratory Work 2: Numerical Solution of a Fredholm Integral Equation

## Overview

This project implements a numerical method for solving a **Fredholm integral equation of the second kind** using the method of successive approximations.

The solution is approximated numerically by applying the **composite Simpson's rule** to evaluate the integral at discrete points.

The convergence of the iterative method is investigated in two functional spaces:

- \(C[0,1]\) — the space of continuous functions with the uniform norm.
- \(L_2[0,1]\) — the space of square-integrable functions with the \(L_2\) norm.

The program also calculates a priori and a posteriori error estimates and visualizes the approximate solution, the exact solution, and the absolute approximation error using **SFML**.

## Objectives

- Study Fredholm integral equations of the second kind.
- Implement the method of successive approximations.
- Apply the composite Simpson's rule for numerical integration.
- Investigate the convergence of the iterative process in \(C[0,1]\) and \(L_2[0,1]\).
- Calculate a priori and a posteriori error estimates.
- Compare numerical and analytical solutions.
- Visualize the obtained results and approximation error.

## Project Structure

```text
Lab2/
├── main.cpp
└── README.md
```

## Requirements

- C++17 compatible compiler
- SFML 2.x
- Standard C++ libraries

## Mathematical Background

### 1. Original Integral Equation

The problem considers the following Fredholm integral equation of the second kind:

$$
x(t)=\lambda\int_0^1 K(t,s)x(s)\,ds+2,
\quad t\in[0,1]
$$

where the kernel is defined as:

$$
K(t,s)=t^2(1+s)
$$

The parameters used in the implementation are:

| Parameter | Value |
|---|---:|
| \(\lambda\) | \(0.4\) |
| Integration interval | \([0,1]\) |
| Step size \(h\) | \(0.05\) |
| Accuracy \(\varepsilon\) | \(10^{-3}\) |
| Number of subintervals | \(20\) |
| Number of grid points | \(21\) |

### 2. Analytical Solution

The exact solution is used to evaluate the accuracy of the numerical approximation.

Assume that the solution has the form:

$$
x(t)=At^2+2
$$

Substituting it into the original equation gives:

$$
At^2+2=
\lambda t^2\int_0^1(1+s)(As^2+2)\,ds+2
$$

Evaluating the integral:

$$
\int_0^1(1+s)(As^2+2)\,ds
=
\frac{7A}{12}+3
$$

Therefore:

$$
A=\lambda\left(\frac{7A}{12}+3\right)
$$

Solving for \(A\):

$$
A(12-7\lambda)=36\lambda
$$

Thus, the analytical solution is:

$$
\boxed{
x_{\text{exact}}(t)=
\frac{36\lambda}{12-7\lambda}t^2+2
}
$$

For \(\lambda=0.4\):

$$
\boxed{
x_{\text{exact}}(t)=
\frac{18}{23}t^2+2
}
$$

### 3. Operator Formulation

The integral equation can be represented as:

$$
x=Ax+f
$$

where the integral operator \(A\) is defined by:

$$
(Ax)(t)=
\lambda\int_0^1 K(t,s)x(s)\,ds
$$

and:

$$
f(t)=2
$$

The solution is obtained through successive approximations:

$$
x_{n+1}=Ax_n+f
$$

or, in expanded form:

$$
\boxed{
x_{n+1}(t)=
\lambda\int_0^1K(t,s)x_n(s)\,ds+2
}
$$

The initial approximation is:

$$
x_0(t)=2
$$

If the operator is a contraction, the sequence of approximations converges to the unique solution of the integral equation.

## Numerical Method

### 1. Discretization of the Integration Interval

The interval \([0,1]\) is divided into \(m\) equal subintervals:

$$
h=\frac{b-a}{m}
$$

The grid points are defined as:

$$
t_i=a+ih,\quad i=0,1,\ldots,m
$$

For the selected parameters:

$$
h=0.05,\qquad m=20
$$

Therefore, the grid contains \(21\) points.

### 2. Composite Simpson's Rule

The integral is evaluated using the composite Simpson's rule:

$$
\int_a^b f(s)\,ds
\approx
\frac{h}{3}
\left[
f_0+f_m+
4\sum_{i=1,3,5,\ldots,m-1}f_i+
2\sum_{i=2,4,6,\ldots,m-2}f_i
\right]
$$

In this implementation:

$$
f(s)=K(t,s)x_n(s)
$$

Consequently, the integral approximation becomes:

$$
\boxed{
\int_0^1K(t,s)x_n(s)\,ds
\approx
\frac{h}{3}
\left[
f_0+f_m+
4\sum_{i=1,3,5,\ldots,m-1}f_i+
2\sum_{i=2,4,6,\ldots,m-2}f_i
\right]
}
$$

where:

$$
f_i=K(t,s_i)x_n(s_i)
$$

The resulting numerical iteration is:

$$
x_{n+1}(t_i)=
\lambda S_h[K(t_i,s)x_n(s)]+2
$$

where \(S_h\) denotes the composite Simpson approximation.

### 3. Convergence in \(C[0,1]\)

The space \(C[0,1]\) is equipped with the uniform norm:

$$
\|x\|_C=
\max_{t\in[0,1]}|x(t)|
$$

The contraction coefficient satisfies:

$$
\|A\|_C\leq
|\lambda|
\max_{t\in[0,1]}
\int_0^1|K(t,s)|\,ds
$$

Since:

$$
|K(t,s)|=t^2(1+s)\leq 2
$$

and the integration interval has length \(1\), we obtain:

$$
\|A\|_C\leq 2|\lambda|
$$

Therefore, the contraction coefficient used in the implementation is:

$$
\boxed{\alpha_C=2|\lambda|}
$$

For \(\lambda=0.4\):

$$
\alpha_C=0.8
$$

Since:

$$
\alpha_C<1
$$

the operator satisfies the contraction condition in \(C[0,1]\).

The norm of the difference between consecutive approximations is calculated as:

$$
\|x_{n+1}-x_n\|_C
=
\max_{0\leq i\leq m}
|x_{n+1}(t_i)-x_n(t_i)|
$$

### 4. Convergence in \(L_2[0,1]\)

The \(L_2\) norm is defined as:

$$
\|x\|_{L_2}=
\sqrt{\int_0^1|x(t)|^2\,dt}
$$

Using the integral operator's kernel, its norm can be bounded by the Hilbert-Schmidt norm:

$$
\|A\|_{L_2}
\leq
|\lambda|
\sqrt{
\int_0^1\int_0^1|K(t,s)|^2\,ds\,dt
}
$$

Substituting the kernel:

$$
\int_0^1\int_0^1t^4(1+s)^2\,ds\,dt
=
\left(\int_0^1t^4\,dt\right)
\left(\int_0^1(1+s)^2\,ds\right)
$$

Evaluating the integrals:

$$
=
\frac{1}{5}\cdot\frac{7}{3}
=
\frac{7}{15}
$$

Thus, the contraction coefficient is bounded by:

$$
\boxed{
\alpha_{L_2}=
|\lambda|\sqrt{\frac{7}{15}}
}
$$

For \(\lambda=0.4\):

$$
\alpha_{L_2}
=
0.4\sqrt{\frac{7}{15}}
\approx 0.273252
$$

Since:

$$
\alpha_{L_2}<1
$$

the operator also satisfies the contraction condition in \(L_2[0,1]\).

The discrete approximation of the \(L_2\) norm used in the program is:

$$
\|x_{n+1}-x_n\|_{L_2}
\approx
\sqrt{
h\sum_{i=0}^{m}
|x_{n+1}(t_i)-x_n(t_i)|^2
}
$$

This expression is evaluated using a rectangular sum over the grid.

### 5. A Priori Error Estimation

For a contraction operator with coefficient \(\alpha\), the a priori error estimate is:

$$
\|x_n-x^*\|
\leq
\frac{\alpha^n}{1-\alpha}
\|x_1-x_0\|
$$

where \(x^*\) is the exact solution.

To guarantee the required accuracy:

$$
\|x_n-x^*\|\leq\varepsilon
$$

it is sufficient to choose \(n\) such that:

$$
\frac{\alpha^n}{1-\alpha}
\|x_1-x_0\|
\leq\varepsilon
$$

Taking logarithms gives the iteration count:

$$
\boxed{
N=
\left\lfloor
\frac{
\ln\left(
\frac{\varepsilon(1-\alpha)}
{\|x_1-x_0\|}
\right)
}{
\ln\alpha
}
\right\rfloor+1
}
$$

The program calculates this estimate independently for both functional spaces.

### 6. A Posteriori Error Estimation

The a posteriori estimate uses the difference between two consecutive approximations:

$$
\boxed{
\|x^*-x_{n+1}\|
\leq
\frac{\alpha}{1-\alpha}
\|x_{n+1}-x_n\|
}
$$

The iteration process stops when:

$$
\frac{\alpha}{1-\alpha}
\|x_{n+1}-x_n\|
\leq\varepsilon
$$

For \(C[0,1]\), the implementation uses:

$$
E_C=
\frac{\alpha_C}{1-\alpha_C}
\max_{0\leq i\leq m}
|x_{n+1}(t_i)-x_n(t_i)|
$$

For \(L_2[0,1]\), it uses:

$$
E_{L_2}=
\frac{\alpha_{L_2}}{1-\alpha_{L_2}}
\sqrt{
h\sum_{i=0}^{m}
|x_{n+1}(t_i)-x_n(t_i)|^2
}
$$

The iterative process terminates when the corresponding error estimate becomes smaller than or equal to the prescribed accuracy.

## Implementation Details

### 1. Integral Evaluation

The `simpson_integral()` function calculates the integral using the composite Simpson's rule.

It applies the following coefficients to the grid values:

- \(1\) for the first and last points.
- \(4\) for odd-indexed interior points.
- \(2\) for even-indexed interior points.

### 2. Successive Approximations

The `solve_integral_equation()` function implements the iterative algorithm.

Its main operations are:

1. Initialize the first approximation with \(x_0(t)=2\).
2. Calculate the first iteration using Simpson's rule.
3. Determine the contraction coefficient for the selected functional space.
4. Calculate the a priori iteration estimate.
5. Perform successive approximations.
6. Calculate the a posteriori error estimate.
7. Stop when the required accuracy is achieved.
8. Display the numerical results.

The function is executed separately for \(C[0,1]\) and \(L_2[0,1]\).

### 3. Exact and Approximate Solutions

The `exact_solution()` function evaluates the analytical solution:

$$
x_{\text{exact}}(t)=
\frac{36\lambda}{12-7\lambda}t^2+2
$$

The numerical approximation is obtained from the iterative algorithm.

Both solutions are used for comparison and visualization.

### 4. Graphical Visualization

The program uses SFML to create two graphical windows.

**Solution Plot**

The first window displays:

- The exact solution in green.
- The approximate numerical solution in blue.
- The coordinate grid and axes.

**Error Plot**

The second window displays the absolute approximation error:

$$
e(t)=
|x_{\text{approx}}(t)-x_{\text{exact}}(t)|
$$

The error curve is displayed in red.

The maximum error over the computational grid is also used to determine the vertical scale of the graph.

## Numerical Analysis

The experiment uses the following parameters:

| Parameter | Value |
|---|---:|
| \(\lambda\) | 0.4 |
| \(\varepsilon\) | 0.001 |
| \(h\) | 0.05 |
| \(m\) | 20 |
| Grid points | 21 |

### Results in \(C[0,1]\)

The calculated contraction coefficient is:

$$
\alpha_C=0.8
$$

The resulting iteration statistics are:

| Metric | Result |
|---|---:|
| Contraction coefficient | 0.80000 |
| A priori iteration count | 39 |
| Actual iteration count | 6 |
| A posteriori error estimate | 0.00077464 |
| Maximum difference from exact solution | 0.00005894 |

### Results in \(L_2[0,1]\)

The calculated contraction coefficient is:

$$
\alpha_{L_2}\approx0.273252
$$

The resulting iteration statistics are:

| Metric | Result |
|---|---:|
| Contraction coefficient | 0.27325 |
| A priori iteration count | 6 |
| Actual iteration count | 4 |
| A posteriori error estimate | 0.00063557 |

The maximum pointwise difference from the analytical solution for the returned \(L_2\) approximation is approximately:

$$
\max_i|x_{\text{approx}}(t_i)-x_{\text{exact}}(t_i)|
\approx0.00108258
$$

The \(L_2\) stopping criterion controls the \(L_2\) error estimate, not the maximum pointwise error. Therefore, this pointwise difference is not required to be smaller than \(\varepsilon\).

### Comparison of Functional Spaces

| Metric | \(C[0,1]\) | \(L_2[0,1]\) |
|---|---:|---:|
| Contraction coefficient | 0.80000 | 0.27325 |
| A priori iterations | 39 | 6 |
| Actual iterations | 6 | 4 |

The contraction coefficient in \(L_2[0,1]\) is smaller than the coefficient used in \(C[0,1]\).

Consequently, the iterative process requires fewer iterations to satisfy the corresponding a posteriori stopping criterion in \(L_2[0,1]\).

## Usage

### Compilation

The project requires SFML 2.x.

Example compilation command using GCC:

```bash
g++ main.cpp -o lab2 -std=c++17 \
    -lsfml-graphics -lsfml-window -lsfml-system
```

### Execution

Run the compiled executable:

```bash
./lab2
```

The program performs the following operations:

1. Constructs the computational grid.
2. Solves the integral equation in \(C[0,1]\).
3. Solves the integral equation in \(L_2[0,1]\).
4. Calculates the maximum difference between the numerical and analytical solutions obtained in \(C[0,1]\).
5. Opens the solution comparison window.
6. Opens the approximation error window after the first window is closed.

## Conclusion

The laboratory work demonstrates the numerical solution of a Fredholm integral equation of the second kind using the method of successive approximations.

The integral operator was investigated in two functional spaces: \(C[0,1]\) and \(L_2[0,1]\). In both cases, the contraction condition is satisfied for the selected parameter \(\lambda=0.4\), guaranteeing convergence of the iterative method.

The composite Simpson's rule was used to approximate the integral, while a priori and a posteriori estimates were applied to analyze the convergence and accuracy of the numerical solution.

The obtained results demonstrate that the iterative process converges in both spaces. The graphical visualization additionally provides a comparison between the analytical and numerical solutions and illustrates the distribution of the approximation error.