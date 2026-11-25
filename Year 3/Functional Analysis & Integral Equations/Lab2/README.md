# Laboratory Work 2: The Contraction Mapping Principle for Integral Equations

## Overview

This repository contains a C++ implementation of the **Contraction Mapping Principle** (Banach Fixed-Point Theorem) for solving a linear Fredholm integral equation of the second kind using the method of successive approximations.

The program discretizes the interval $[0, 1]$, approximates the integral operator using **Simpson's rule**, analyzes convergence in two function spaces ($C[0,1]$ and $L_2[0,1]$), estimates the required number of iterations using an a priori error bound, stops based on an a posteriori error estimate, compares the numerical result against a closed-form solution, and visualizes both the solutions and the pointwise error using the **SFML** graphics library.

All numerical computations are implemented manually using the C++ standard library without external mathematical libraries.

---

## Objectives

- Study the **Contraction Mapping Principle** applied to integral operators in normed function spaces.
- Formulate a fixed-point iteration scheme for a Fredholm integral equation of the second kind.
- Evaluate contraction coefficients in the uniform space $C[0,1]$ and the Hilbert space $L_2[0,1]$.
- Approximate definite integrals numerically using Simpson's rule on a uniform grid.
- Estimate the number of iterations via an a priori error bound and control termination via an a posteriori error bound.
- Compare the approximate solution with the exact analytical solution.
- Visualize the approximate vs. exact solutions and the absolute error curve using SFML.

---

## Project Structure

```text
.
├── main.cpp       # Numerical solver, error estimation, and SFML plotting routines
└── README.md      # This file
```

---

## Requirements

- C++17 or higher
- GCC, Clang, or MSVC compiler
- SFML 2.x graphics library (`graphics`, `window`, `system`)
- A TrueType font (`.ttf`, e.g., `C:/Windows/Fonts/arial.ttf` as configured in `main.cpp`) for axis and legend labels

SFML is used exclusively for graphical visualization. All mathematical calculations are performed using the C++ standard library.

---

## Mathematical Background

### 1. Integral Equation and Fixed-Point Operator

The program solves a Fredholm integral equation of the second kind on $t \in [0, 1]$:

$$
x(t) = \lambda \int_{0}^{1} K(t, s)\,x(s)\,ds + 2
$$

with kernel:

$$
K(t, s) = t^2(1 + s)
$$

and parameter $\lambda = 0.4$. This defines the fixed-point iteration operator:

$$
(Ax)(t) = \lambda \int_{0}^{1} t^2(1 + s)\,x(s)\,ds + 2
$$

The corresponding exact solution for parameter $\lambda$ is:

$$
x_{\text{exact}}(t) = \frac{36\lambda}{12 - 7\lambda}\,t^2 + 2
$$

For $\lambda = 0.4$:

$$
x_{\text{exact}}(t) = \frac{36 \cdot 0.4}{12 - 7 \cdot 0.4}\,t^2 + 2 = \frac{14.4}{9.2}\,t^2 + 2 = \frac{36}{23}\,t^2 + 2 \approx 1.56522\,t^2 + 2
$$

### 2. Contraction in Function Spaces

According to the **Banach Fixed-Point Theorem**, if an operator $A$ maps a complete metric space into itself and is a contraction with contraction coefficient $\alpha < 1$, it has a unique fixed point to which successive approximations $x_{n+1} = Ax_n$ converge.

The implementation evaluates two spaces on $[0, 1]$:

- **Uniform space $C[0,1]$** (Chebyshev norm $\|u\|_{C[0,1]} = \max_{t \in [0,1]} |u(t)|$):

$$
\alpha_{C} = 2|\lambda|
$$

For $\lambda = 0.4$:

$$
\boxed{\alpha_{C} = 0.8}
$$

- **Square-integrable space $L_2[0,1]$** ($L_2$ norm $\|u\|_{L_2[0,1]} = \left(\int_0^1 |u(t)|^2\,dt\right)^{1/2}$):

$$
\alpha_{L_2} = |\lambda|\sqrt{\frac{7}{15}}
$$

For $\lambda = 0.4$:

$$
\boxed{\alpha_{L_2} \approx 0.27325}
$$

In both spaces, $0 < \alpha < 1$, guaranteeing contraction.

---

## Numerical Method

### 1. Grid Discretization and Simpson's Rule

The interval $[a, b] = [0, 1]$ is partitioned into $m = 20$ subintervals of step size $h = 0.05$, producing $m + 1 = 21$ grid nodes $t_i = a + i h$ ($i = 0, \dots, m$).

At each grid node $t_i$, the integral $\int_0^1 K(t_i, s) x_{\text{prev}}(s)\,ds$ is evaluated via the composite **Simpson's rule** (`simpson_integral`), weighting boundary nodes by $1$, odd interior nodes by $4$, and even interior nodes by $2$, then multiplying by $h / 3$.

### 2. Successive Approximations

Starting from the initial approximation $x_0(t) = 2.0$ at all grid points, the program computes $x_1 = Ax_0$ and iterates:

$$
x_{n+1}(t_i) = \lambda\,\mathcal{I}_{\text{Simpson}}\!\big(K(t_i, \cdot)\,x_n(\cdot)\big) + 2
$$

### 3. A Priori Error Estimation

Using the norm difference $\|x_1 - x_0\|$ in the active space ($C[0,1]$ or $L_2[0,1]$) and target accuracy $\varepsilon = 10^{-3}$, the a priori iteration count is estimated as:

$$
N_{\text{apriori}} = \left\lfloor \frac{\ln\!\left(\frac{\varepsilon(1 - \alpha)}{\|x_1 - x_0\|}\right)}{\ln(\alpha)} \right\rfloor + 1
$$

### 4. A Posteriori Error Estimation

At each iteration $n$, the program computes the difference between consecutive iterates $\|x_{n+1} - x_n\|$ (using the maximum absolute difference in $C[0,1]$ and the discrete $L_2$ norm in $L_2[0,1]$) and evaluates:

$$
\text{error}_{n+1} = \frac{\alpha}{1 - \alpha}\,\|x_{n+1} - x_n\|
$$

The loop stops when:

$$
\boxed{\frac{\alpha}{1 - \alpha}\,\|x_{n+1} - x_n\| \le \varepsilon}
$$

(with a safety cap of $10{,}000$ iterations).

---

## Implementation Details

The program is written in **C++** and structured around the following functions:

| Function | Description |
|---|---|
| `exact_solution(t, lambda)` | Evaluates the analytical solution $x_{\text{exact}}(t)$ at point `t` for given `lambda` |
| `K(t, s)` | Defines the integral kernel $K(t, s) = t^2(1 + s)$ |
| `simpson_integral(...)` | Numerically integrates $K(t, s)x_{\text{prev}}(s)$ over `[0, 1]` using Simpson's rule |
| `format_number(value)` | Formats axis tick labels cleanly with up to two decimal places |
| `solve_integral_equation(...)` | Runs successive approximations in $C[0,1]$ (`space_type = 0`) or $L_2[0,1]$ (`space_type = 1`) and prints convergence metrics |
| `draw_solution_plot(...)` | Opens an SFML window comparing approximate (`x_approx`) and exact (`exact_solution`) curves |
| `draw_error_plot(...)` | Opens an SFML window plotting the absolute error $\|x_{\text{approx}}(t) - x_{\text{exact}}(t)\|$ over `[0, 1]` |
| `main()` | Configures parameters, solves in both spaces, prints max error vs. exact solution, and launches both plots |

### Numerical Parameters

| Parameter | Value | Description |
|---|---:|---|
| $\lambda$ | `0.4` | Integral equation parameter |
| $\varepsilon$ | `1e-3` ($0.001$) | Required accuracy threshold |
| $[a, b]$ | $[0.0, 1.0]$ | Domain interval |
| $h$ | `0.05` | Grid step size ($20$ subintervals, $21$ nodes) |
| $x_0(t)$ | `2.0` | Initial approximation on the grid |
| $\alpha_C$ | `0.8` | Contraction coefficient in $C[0,1]$ |
| $\alpha_{L_2}$ | $\approx 0.27325$ | Contraction coefficient in $L_2[0,1]$ |

---

## Graphical Visualization

After printing the numerical results to the console, the program opens two sequential SFML windows (`1000x700` pixels):

1. **Solution Comparison Window** (`"Variant 1.16: Solutions (lambda = 0.4)"`):
   - Plots `x_approx` in **blue** and `exact_solution` in **green** over $t \in [0, 1]$ and $y \in [1.5, 4.0]$.
   - Draws a coordinate grid with step `0.05`, axis labels, and a legend.
2. **Error Plot Window** (`"Error: |approximate - exact| (lambda = 0.4)"`):
   - Plots $|x_{\text{approx}}(t_i) - x_{\text{exact}}(t_i)|$ in **red** across the grid nodes.
   - Automatically scales the vertical axis based on the maximum error (rounded up to `0.001`, with a floor of `1e-5`).

> **Note:** `draw_solution_plot` and `draw_error_plot` run sequentially—closing the first SFML window opens the second one. Also check the font path `"C:/Windows/Fonts/arial.ttf"` if running on Linux or macOS.

---

## Usage

### Compilation

Compile `main.cpp` with C++17 and link SFML 2.x:

```bash
g++ -std=c++17 -O2 main.cpp -o integral_contraction \
    -I/path/to/SFML/include \
    -L/path/to/SFML/lib \
    -lsfml-graphics -lsfml-window -lsfml-system -lm
```

Adjust include/library paths and font path as needed for your operating system and SFML installation.

### Execution

Run the compiled binary:

```bash
./integral_contraction
```

On Windows:

```bash
integral_contraction.exe
```

---

## Output

For each space (`C[0,1]` and `L2[0,1]`), the console prints:

- Contraction coefficient ($\alpha$)
- A priori iteration count
- Actual iteration count
- A posteriori error estimate

Followed by the maximum pointwise difference between the $C[0,1]$ approximate solution and the exact solution across all grid points:

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

---

## Conclusion

This laboratory work applies the **Contraction Mapping Principle** to solve a Fredholm integral equation of the second kind numerically via successive approximations and Simpson's quadrature.

Comparing the $C[0,1]$ and $L_2[0,1]$ norms highlights how the choice of function space affects the contraction coefficient $\alpha$, iteration estimates, and error bounds, while comparing against the closed-form solution and plotting both curves and errors in SFML provides clear verification of convergence.