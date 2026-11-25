# Laboratory Work 2: Numerical Solution of a Fredholm Integral Equation

## Overview

This project implements a numerical method for solving a **Fredholm integral equation of the second kind** using the method of successive approximations.

The integral is evaluated numerically using the **composite Simpson's rule**. The convergence of the iterative process is investigated in two functional spaces:

- `C[0,1]` — the space of continuous functions with the uniform norm.
- `L2[0,1]` — the space of square-integrable functions with the L2 norm.

The program calculates a priori and a posteriori error estimates, compares the numerical approximation with the analytical solution, and visualizes the results using **SFML**.

## Objectives

- Study Fredholm integral equations of the second kind.
- Implement the method of successive approximations.
- Apply the composite Simpson's rule for numerical integration.
- Investigate convergence in `C[0,1]` and `L2[0,1]`.
- Calculate a priori and a posteriori error estimates.
- Compare numerical and analytical solutions.
- Visualize the approximate solution and its absolute error.

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
x(t) = \lambda \int_0^1 K(t,s)x(s)\,ds + 2
$$

where:

$$
t \in [0,1]
$$

and the kernel is:

$$
K(t,s) = t^2(1+s)
$$

The parameters used in the implementation are:

| Parameter | Value |
|---|---:|
| Lambda | 0.4 |
| Integration interval | [0, 1] |
| Step size `h` | 0.05 |
| Accuracy `epsilon` | 0.001 |
| Number of subintervals | 20 |
| Number of grid points | 21 |

### 2. Analytical Solution

The exact solution is used to evaluate the accuracy of the numerical approximation.

Assume that the solution has the form:

$$
x(t) = At^2 + 2
$$

Substituting it into the original equation gives:

$$
At^2 + 2 =
\lambda t^2 \int_0^1 (1+s)(As^2+2)\,ds + 2
$$

Evaluating the integral:

$$
\int_0^1 (1+s)(As^2+2)\,ds
=
\frac{7A}{12} + 3
$$

Therefore:

$$
A = \lambda \left(\frac{7A}{12}+3\right)
$$

Rearranging the equation:

$$
A(12-7\lambda) = 36\lambda
$$

Thus, the analytical solution is:

$$
x_{\text{exact}}(t)
=
\frac{36\lambda}{12-7\lambda}t^2+2
$$

For `lambda = 0.4`:

$$
x_{\text{exact}}(t)
=
\frac{36}{23}t^2+2
$$

### 3. Operator Formulation

The integral equation can be represented in operator form:

$$
x = Ax + f
$$

where the integral operator is:

$$
(Ax)(t) =
\lambda \int_0^1 K(t,s)x(s)\,ds
$$

and the free term is:

$$
f(t)=2
$$

The solution is obtained using successive approximations:

$$
x_{n+1}=Ax_n+f
$$

In expanded form:

$$
x_{n+1}(t)
=
\lambda \int_0^1 K(t,s)x_n(s)\,ds+2
$$

The initial approximation is:

$$
x_0(t)=2
$$

If the operator is a contraction, the sequence of approximations converges to the unique solution of the integral equation.

## Numerical Method

### 1. Discretization of the Integration Interval

The integration interval `[0, 1]` is divided into `m` equal subintervals.

The step size is calculated as:

$$
h=\frac{b-a}{m}
$$

The grid points are defined by:

$$
t_i=a+ih
$$

where:

$$
i=0,1,2,\ldots,m
$$

For the selected parameters:

$$
h=0.05,\qquad m=20
$$

Therefore, the computational grid contains 21 points.

### 2. Composite Simpson's Rule

The integral is evaluated using the composite Simpson's rule.

For an even number of subintervals, the formula is:

$$
\int_a^b f(s)\,ds
\approx
\frac{h}{3}
\left[
f_0+f_m
+4\sum_{i=1,3,5,\ldots,m-1}f_i
+2\sum_{i=2,4,6,\ldots,m-2}f_i
\right]
$$

In this implementation, the integrand is:

$$
f(s)=K(t,s)x_n(s)
$$

At the grid points:

$$
f_i=K(t,s_i)x_n(s_i)
$$

Consequently, the integral approximation becomes:

$$
\int_0^1 K(t,s)x_n(s)\,ds
\approx
\frac{h}{3}
\left[
f_0+f_m
+4\sum_{i=1,3,5,\ldots,m-1}f_i
+2\sum_{i=2,4,6,\ldots,m-2}f_i
\right]
$$

The resulting numerical iteration is:

$$
x_{n+1}(t_i)
=
\lambda S_h[K(t_i,s)x_n(s)]+2
$$

where `S_h` denotes the composite Simpson approximation.

### 3. Convergence in C[0,1]

The space `C[0,1]` is equipped with the uniform norm:

$$
\|x\|_C =
\max_{t\in[0,1]}|x(t)|
$$

The norm of the integral operator can be bounded as follows:

$$
\|A\|_C
\leq
|\lambda|
\max_{t\in[0,1]}
\int_0^1 |K(t,s)|\,ds
$$

Since:

$$
|K(t,s)|=t^2(1+s)\leq 2
$$

and the integration interval has length 1, we obtain the following upper bound:

$$
\|A\|_C\leq 2|\lambda|
$$

Therefore, the contraction coefficient used in the implementation is:

$$
\alpha_C=2|\lambda|
$$

For `lambda = 0.4`:

$$
\alpha_C=0.8
$$

Since:

$$
\alpha_C<1
$$

the contraction condition is satisfied in `C[0,1]`.

The norm of the difference between consecutive approximations is calculated as:

$$
\|x_{n+1}-x_n\|_C
=
\max_{i=0,1,\ldots,m}
|x_{n+1}(t_i)-x_n(t_i)|
$$

### 4. Convergence in L2[0,1]

The L2 norm is defined as:

$$
\|x\|_{L_2}
=
\sqrt{\int_0^1 |x(t)|^2\,dt}
$$

The norm of the integral operator can be bounded using the Hilbert-Schmidt norm:

$$
\|A\|_{L_2}
\leq
|\lambda|
\sqrt{
\int_0^1\int_0^1 |K(t,s)|^2\,ds\,dt
}
$$

Substituting the kernel:

$$
\int_0^1\int_0^1 t^4(1+s)^2\,ds\,dt
$$

Separating the integrals:

$$
=
\left(\int_0^1 t^4\,dt\right)
\left(\int_0^1 (1+s)^2\,ds\right)
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
\alpha_{L_2}
=
|\lambda|\sqrt{\frac{7}{15}}
$$

For `lambda = 0.4`:

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

the contraction condition is also satisfied in `L2[0,1]`.

The program approximates the L2 norm of the difference between consecutive iterations using a discrete sum:

$$
\|x_{n+1}-x_n\|_{L_2}
\approx
\sqrt{
h\sum_{i=0}^{m}
|x_{n+1}(t_i)-x_n(t_i)|^2
}
$$

This is the rectangular-sum approximation used in the implementation.

### 5. A Priori Error Estimation

For a contraction operator with coefficient `alpha`, the a priori error estimate is:

$$
\|x_n-x^*\|
\leq
\frac{\alpha^n}{1-\alpha}
\|x_1-x_0\|
$$

where `x*` is the exact solution.

To guarantee the required accuracy:

$$
\|x_n-x^*\|\leq\varepsilon
$$

it is sufficient to choose `n` such that:

$$
\frac{\alpha^n}{1-\alpha}
\|x_1-x_0\|
\leq\varepsilon
$$

Taking logarithms gives the iteration count used in the program:

$$
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
$$

The program calculates this estimate independently for both functional spaces.

### 6. A Posteriori Error Estimation

The a posteriori estimate uses the difference between two consecutive approximations:

$$
\|x^*-x_{n+1}\|
\leq
\frac{\alpha}{1-\alpha}
\|x_{n+1}-x_n\|
$$

The iterative process stops when:

$$
\frac{\alpha}{1-\alpha}
\|x_{n+1}-x_n\|
\leq\varepsilon
$$

For `C[0,1]`, the implementation calculates:

$$
E_C=
\frac{\alpha_C}{1-\alpha_C}
\max_{i=0,1,\ldots,m}
|x_{n+1}(t_i)-x_n(t_i)|
$$

For `L2[0,1]`, it calculates:

$$
E_{L_2}=
\frac{\alpha_{L_2}}{1-\alpha_{L_2}}
\sqrt{
h\sum_{i=0}^{m}
|x_{n+1}(t_i)-x_n(t_i)|^2
}
$$

The iteration terminates when the corresponding error estimate becomes smaller than or equal to the prescribed accuracy.

## Implementation Details

### 1. Integral Evaluation

The `simpson_integral()` function calculates the integral using the composite Simpson's rule.

It applies the following coefficients to the grid values:

- `1` for the first and last points.
- `4` for odd-indexed interior points.
- `2` for even-indexed interior points.

### 2. Successive Approximations

The `solve_integral_equation()` function implements the iterative algorithm.

Its main operations are:

1. Initialize the first approximation with `x0(t) = 2`.
2. Calculate the first iteration using Simpson's rule.
3. Determine the contraction coefficient for the selected functional space.
4. Calculate the a priori iteration estimate.
5. Perform successive approximations.
6. Calculate the a posteriori error estimate.
7. Stop when the required accuracy is achieved.
8. Display the numerical results.

The function is executed separately for `C[0,1]` and `L2[0,1]`.

### 3. Exact and Approximate Solutions

The `exact_solution()` function evaluates the analytical solution:

$$
x_{\text{exact}}(t)
=
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

The maximum error over the computational grid is used to determine the vertical scale of the graph.

## Numerical Analysis

The experiment uses the following parameters:

| Parameter | Value |
|---|---:|
| `lambda` | 0.4 |
| `epsilon` | 0.001 |
| `h` | 0.05 |
| `m` | 20 |
| Grid points | 21 |

### Results in C[0,1]

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

### Results in L2[0,1]

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

The maximum pointwise difference from the analytical solution for the returned L2 approximation is approximately:

$$
\max_{i=0,1,\ldots,m}
|x_{\text{approx}}(t_i)-x_{\text{exact}}(t_i)|
\approx 0.00108258
$$

The L2 stopping criterion controls the L2 error estimate, not the maximum pointwise error. Therefore, the maximum pointwise difference is not required to be smaller than `epsilon`.

### Comparison of Functional Spaces

| Metric | C[0,1] | L2[0,1] |
|---|---:|---:|
| Contraction coefficient | 0.80000 | 0.27325 |
| A priori iterations | 39 | 6 |
| Actual iterations | 6 | 4 |

The contraction coefficient in `L2[0,1]` is smaller than the coefficient used in `C[0,1]`.

Consequently, the iterative process requires fewer iterations to satisfy the corresponding a posteriori stopping criterion in `L2[0,1]`.

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
2. Solves the integral equation in `C[0,1]`.
3. Solves the integral equation in `L2[0,1]`.
4. Calculates the maximum difference between the numerical and analytical solutions obtained in `C[0,1]`.
5. Opens the solution comparison window.
6. Opens the approximation error window after the first window is closed.

## Conclusion

The laboratory work demonstrates the numerical solution of a Fredholm integral equation of the second kind using the method of successive approximations.

The integral operator was investigated in two functional spaces: `C[0,1]` and `L2[0,1]`. In both cases, the contraction condition is satisfied for the selected parameter `lambda = 0.4`, guaranteeing convergence of the iterative method in the corresponding spaces.

The composite Simpson's rule was used to approximate the integral, while a priori and a posteriori estimates were applied to analyze the convergence and accuracy of the numerical solution.

The obtained results demonstrate that the iterative process converges in both spaces. The graphical visualization additionally provides a comparison between the analytical and numerical solutions and illustrates the distribution of the approximation error.