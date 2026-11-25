# Functional Analysis & Integral Equations — Lab Work Collection

This repository contains a comprehensive collection of **Functional Analysis and Integral Equations** laboratory works, implemented in **C++** with a strong emphasis on **numerical accuracy**, **mathematical rigor**, and **graphical visualization**.

The projects focus on the practical application of the **Contraction Mapping Principle** (Banach Fixed-Point Theorem), **successive approximation methods**, **a priori and a posteriori error estimation**, **numerical quadrature**, and **convergence analysis across normed function spaces**.

All numerical algorithms are implemented from scratch using the **C++ standard library** without external mathematical solvers, while **SFML** is used exclusively for interactive graphical plotting of functions, approximate solutions, and error distributions.

---

## Overview

- Total of **2 laboratory works** covering nonlinear algebraic equations and linear Fredholm integral equations
- All laboratory works are implemented as **independent, self-contained C++ projects**
- Each assignment bridges **abstract functional analysis theory** with **concrete numerical computation**
- Mathematical formulas and parameters are verified analytically and numerically
- Includes **real-time graphical visualization** of functions, exact vs. approximate curves, and pointwise errors

The repository reflects a **progressive mathematical path**, starting from fixed-point iterations in finite-dimensional Euclidean intervals ($\mathbb{R}$) and advancing to contraction operators in infinite-dimensional normed function spaces ($C[0,1]$ and $L_2[0,1]$).

---

## Development Environment

- **Language standard**: C++17 or higher
- **Compilers**: GCC, Clang, or MSVC
- **IDE**:
  - **Microsoft Visual Studio 2026** — C++ development and debugging
- **Graphics library**:
  - **SFML 2.x** (`sfml-graphics`, `sfml-window`, `sfml-system`) — Cartesian grid rendering, curve plotting, and error visualization
- **Core libraries**:
  - C++ Standard Library (`<cmath>`, `<vector>`, `<iomanip>`, `<algorithm>`, `<sstream>`) — manual implementation of all numerical methods

---

## Laboratory Works

### **Lab 1 — The Contraction Mapping Principle for Algebraic Equations**
- Transformation of a nonlinear algebraic equation $g(x) = 3x + \sin(x) + \sqrt{1 + x^2} = 0$ into an equivalent fixed-point form $x = f(x) = x - \lambda g(x)$ on $[-1, 0]$
- Determination of the optimal iteration parameter $\lambda$ and contraction coefficient $\alpha$ using derivative bounds ($k_1, k_2$)
- Implementation of the **successive approximation method** ($x_{n+1} = f(x_n)$)
- Calculation of the **a priori iteration estimate** ($N$) and **a posteriori stopping criterion** ($\frac{\alpha}{1 - \alpha}\vert{}x_{n+1} - x_n\vert{} \le \varepsilon$)
- Residual verification ($\vert{}g(x^{\ast})\vert{} < \varepsilon$)
- Graphical visualization of $g(x)$ and its approximate root marker using **SFML**

---

### **Lab 2 — The Contraction Mapping Principle for Integral Equations**
- Numerical solution of a linear Fredholm integral equation of the second kind:
  $$x(t) = \lambda \int_{0}^{1} t^2(1 + s)\,x(s)\,ds + 2$$
- Discretization of $[0, 1]$ on a uniform grid ($h = 0.05$) and numerical integration via **composite Simpson's rule**
- Comparative convergence analysis in two normed function spaces:
  - **Uniform space** $C[0,1]$ ($\alpha_C = 2\vert{}\lambda\vert{}$)
  - **Square-integrable Hilbert space** $L_2[0,1]$ ($\alpha_{L_2} = \vert{}\lambda\vert{}\sqrt{7/15}$)
- A priori iteration count estimation and a posteriori norm-based termination
- Benchmarking against the closed-form analytical solution $x_{\text{exact}}(t) = \frac{36\lambda}{12 - 7\lambda}t^2 + 2$
- Dual **SFML** visualization: approximate vs. exact solution curves and pointwise absolute error $\vert{}x_{\text{approx}}(t) - x_{\text{exact}}(t)\vert{}$

---

## Key Concepts Covered

- Banach Fixed-Point Theorem (Contraction Mapping Principle)
- Metric and normed spaces ($\mathbb{R}$, $C[a,b]$, $L_2[a,b]$)
- Contraction operators and Lipschitz / derivative bounds
- Method of successive approximations (Picard iterations)
- A priori and a posteriori error bounds
- Fredholm integral equations of the second kind
- Composite Simpson's quadrature rule
- Analytical vs. numerical error verification
- Scientific data visualization with SFML

---

## Purpose of This Repository

This repository serves as:

- A **complete reference** for computational methods in Functional Analysis and Integral Equations
- A demonstration of **clean, dependency-free numerical C++ programming**
- A structured collection of **academic laboratory works** with full mathematical documentation
- A practical bridge between **operator theory** and **scientific computing**

---

## License

Educational projects developed as part of the **Functional Analysis and Integral Equations** course.