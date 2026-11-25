# Laboratory Work 1: The Contraction Mapping Principle for Algebraic Equations

## Overview

This repository contains a C++ implementation of the **Contraction Mapping Principle** (Banach Fixed-Point Theorem) for solving nonlinear algebraic equations.

The work focuses on transforming a nonlinear equation into an equivalent fixed-point equation, determining the optimal iteration parameter, estimating the required number of iterations, and obtaining an approximate solution using the successive approximation method.

The implementation also includes a graphical visualization of the original function using the **SFML** graphics library.

All numerical calculations are implemented manually using the C++ standard library without external mathematical libraries.

---

## Objectives

* Study the **Contraction Mapping Principle** and its application to nonlinear equations.
* Transform the original algebraic equation into an equivalent fixed-point form.
* Determine the optimal iteration parameter using derivative bounds.
* Calculate the contraction coefficient.
* Estimate the required number of iterations using an a priori error bound.
* Implement the successive approximation method.
* Apply an a posteriori error estimation to determine the stopping condition.
* Verify the obtained numerical solution.
* Visualize the original function and its approximate root using SFML.

---

## Project Structure

```text
.
├── main.cpp       # Implementation of the numerical method and graphical visualization
└── README.md      # This file
```

---

## Requirements

* C++17 or higher
* GCC, Clang, or MSVC compiler
* SFML 2.x graphics library (`graphics`, `window`, `system`)
* A TrueType font (`.ttf`) for graphical labels

SFML is used exclusively for graphical visualization. All mathematical calculations are performed using the standard C++ library.

---

## Mathematical Background

### 1. Original Algebraic Equation

The problem is to find a root of the nonlinear algebraic equation:

$$
g(x) = 3x + \sin(x) + \sqrt{1 + x^2} = 0
$$

The solution is searched for in the interval:

$$
x \in [-1, 0]
$$

The original equation is transformed into an equivalent fixed-point equation:

$$
x = f(x)
$$

where the iteration function is defined as:

$$
f(x) = x - \lambda g(x)
$$

Here, $\lambda$ is a parameter selected to satisfy the contraction condition.

### 2. Contraction Mapping Principle

According to the **Banach Fixed-Point Theorem**, if a function $f(x)$ maps a closed interval into itself and satisfies the contraction condition:

$$
\vert{}f'(x)\vert{} \leq \alpha < 1
$$

then it has exactly one fixed point in that interval.

The fixed point can be obtained using the successive approximation method:

$$
x_{n+1} = f(x_n)
$$

For the given function, the derivative is:

$$
g'(x) = 3 + \cos(x) + \frac{x}{\sqrt{1 + x^2}}
$$

The implementation uses the following derivative bounds on the selected interval:

$$
k_1 = 2.833, \qquad k_2 = 4.0
$$

These bounds are used to determine the iteration parameter and the contraction coefficient.

### 3. Optimal Iteration Parameter

The iteration parameter is calculated using the formula:

$$
\lambda = \frac{2}{k_1 + k_2}
$$

Substituting the assigned values:

$$
\lambda = \frac{2}{2.833 + 4.0}
$$

$$
\boxed{\lambda \approx 0.292697}
$$

The resulting iteration function is:

$$
f(x) = x - 0.292697\left(3x + \sin(x) + \sqrt{1 + x^2}\right)
$$

### 4. Contraction Coefficient

The contraction coefficient is calculated as:

$$
\alpha = \frac{k_2 - k_1}{k_2 + k_1}
$$

Substituting the derivative bounds:

$$
\alpha = \frac{4.0 - 2.833}{4.0 + 2.833}
$$

$$
\boxed{\alpha \approx 0.170789}
$$

Since:

$$
0 < \alpha < 1
$$

the iteration function satisfies the contraction condition.

Additionally, the function maps the selected interval into itself, satisfying the requirements of the Banach Fixed-Point Theorem.

---

## Numerical Method

### 1. Successive Approximation Method

The nonlinear equation is solved using the fixed-point iteration formula:

$$
x_{n+1} = f(x_n)
$$

Substituting the definition of $f(x)$:

$$
x_{n+1} = x_n - \lambda g(x_n)
$$

The initial approximation is:

$$
x_0 = -0.5
$$

The first iteration is calculated as:

$$
x_1 = f(x_0)
$$

$$
x_1 = -0.5 - 0.292697 \cdot g(-0.5)
$$

$$
x_1 \approx -0.247873
$$

Each subsequent approximation is calculated using the previous result until the required accuracy is achieved.

### 2. A Priori Error Estimation

Before executing the iterative algorithm, the program calculates an estimate of the number of iterations required to achieve the specified accuracy.

The a priori error bound is:

$$
\vert{}x_n - x^*\vert{} \leq \frac{\alpha^n}{1 - \alpha}\vert{}x_1 - x_0\vert{}
$$

where:

* $x^*$ is the exact fixed point;
* $\alpha$ is the contraction coefficient;
* $x_0$ is the initial approximation;
* $x_1$ is the first approximation;
* $\varepsilon$ is the required accuracy.

The number of iterations is estimated using:

$$
N = \left\lfloor \frac{\ln\!\left(\frac{\varepsilon(1 - \alpha)}{\vert{}x_1 - x_0\vert{}}\right)}{\ln(\alpha)} \right\rfloor + 1
$$

The implementation uses:

$$
\varepsilon = 10^{-4}
$$

The resulting estimate for the assigned parameters is:

$$
\boxed{N = 5}
$$

### 3. A Posteriori Error Estimation

During the iterative process, the program evaluates the error using the difference between two consecutive approximations.

The a posteriori error bound is:

$$
\vert{}x^* - x_{n+1}\vert{} \leq \frac{\alpha}{1 - \alpha}\vert{}x_{n+1} - x_n\vert{}
$$

The iterative process terminates when:

$$
\boxed{\frac{\alpha}{1 - \alpha}\vert{}x_{n+1} - x_n\vert{} \leq \varepsilon}
$$

This condition provides an upper bound on the distance between the current approximation and the exact solution.

Unlike the a priori estimate, the a posteriori estimate uses the actual difference between consecutive iterations.

---

## Implementation Details

The program is implemented in **C++** and consists of several logical components:

| Function | Description |
| :--- | :--- |
| `g(x)` | Defines the original nonlinear equation |
| `f(x, lambda)` | Implements the fixed-point iteration function |
| `calculate_apriori_iterations()` | Calculates the a priori iteration estimate |
| `format_number()` | Formats floating-point values for graphical labels |
| `plot_graph()` | Creates a graphical representation of the original function |
| `main()` | Initializes parameters, performs iterations, and displays results |

### Numerical Parameters

The following parameters are used in the implementation:

| Parameter | Value | Description |
| :--- | ---: | :--- |
| $k_1$ | `2.833` | Lower derivative bound |
| $k_2$ | `4.0` | Upper derivative bound |
| $\varepsilon$ | $10^{-4}$ | Required accuracy |
| $x_0$ | `-0.5` | Initial approximation |
| $\lambda$ | `0.292697` | Iteration parameter |
| $\alpha$ | `0.170789` | Contraction coefficient |
| $N$ | `5` | A priori iteration estimate |

---

## Graphical Visualization

The application uses **SFML** to visualize the original nonlinear function:

$$
g(x) = 3x + \sin(x) + \sqrt{1 + x^2}
$$

The graph is plotted over the interval:

$$
x \in [-1, 0]
$$

The visualization includes:

* A Cartesian coordinate system with labeled axes.
* A grid with a step of `0.05` along both axes.
* The graph of the original function.
* A highlighted red marker indicating the approximate root.
* Automatic scaling to preserve the proportions of the coordinate system.
* Numerical labels along the coordinate axes.

The graph is generated using `2001` sampling points, providing a smooth visual representation of the function.

The approximate root marker is positioned at:

$$
x \approx -0.2590
$$

---

## Numerical Analysis

The program evaluates the obtained solution using the original nonlinear equation.

### 1. Approximate Solution

After completing the iterative process, the program obtains:

$$
\boxed{x^* \approx -0.258976}
$$

### 2. Actual Number of Iterations

The iterative process terminates after:

$$
\boxed{N_{\text{actual}} = 3}
$$

The actual number of iterations can be smaller than the a priori estimate because the latter provides a theoretical upper bound based on the initial approximation.

### 3. Solution Verification

To verify the obtained result, the program substitutes the approximate solution into the original equation:

$$
g(x^{\ast}) = 3x^{\ast} + \sin(x^{\ast}) + \sqrt{1 + (x^{\ast})^2}
$$

For the calculated approximation:

$$
g(-0.258976) \approx -2.83 \cdot 10^{-5}
$$

Since:

$$
\vert{}g(x^*)\vert{} < 10^{-4}
$$

the obtained approximation satisfies the required accuracy.

---

## Usage

### Compilation

The project requires SFML 2.x to be installed and properly configured.

Example compilation using GCC:

```bash
g++ -std=c++17 -O2 main.cpp -o contraction_method \
    -I/path/to/SFML/include \
    -L/path/to/SFML/lib \
    -lsfml-graphics -lsfml-window -lsfml-system
```

Adjust the include and library paths according to your SFML installation.

### Execution

Run the compiled executable:

```bash
./contraction_method
```

On Windows:

```bash
contraction_method.exe
```

Make sure that the required SFML runtime libraries and a compatible `.ttf` font are available.

The program first performs the numerical calculations and displays the results in the console. It then opens an SFML window containing the graph of the original function.

---

## Output

The console output contains:

* A priori estimate of the required number of iterations.
* Actual number of iterations performed.
* Approximate solution.
* Verification result obtained by evaluating the original function at the approximate solution.

**Example output:**

```text
A priori iteration estimate: 5
Actual number of iterations: 3
Approximate solution: -0.258976
Verification (g(x)): -0.000028
```

The graphical window displays the original function and the approximate location of its root.

---

## Results Summary

| Parameter | Result |
| :--- | ---: |
| Iteration parameter ($\lambda$) | `0.292697` |
| Contraction coefficient ($\alpha$) | `0.170789` |
| Initial approximation ($x_0$) | `-0.5` |
| Required accuracy ($\varepsilon$) | $10^{-4}$ |
| A priori iteration estimate | `5` |
| Actual number of iterations | `3` |
| Approximate solution | `-0.258976` |
| Function value at the solution | $-2.83 \cdot 10^{-5}$ |

The numerical results demonstrate that the successive approximation method converges to the root of the original nonlinear equation while satisfying the specified accuracy.

---

## Conclusion

This laboratory work demonstrates the practical application of the **Contraction Mapping Principle** to solving nonlinear algebraic equations.

The original equation is transformed into an equivalent fixed-point problem, and the iteration parameter is selected using derivative bounds to ensure convergence.

The implementation combines the successive approximation method with both a priori and a posteriori error estimation, making it possible to predict the required number of iterations and determine when the desired accuracy has been achieved.

Additionally, the SFML graphical component provides a visual representation of the original function and allows the approximate root to be examined graphically.

The results confirm the effectiveness of the contraction mapping approach as a numerical method for solving nonlinear equations.