# Laboratory Work 2: Mixture of Two Gaussian Distributions (Manual Implementation)

## Overview

This repository contains a **from-scratch (manual) implementation** of **Laboratory Work 2** on modeling and analyzing a **mixture of two Gaussian distributions**.

Unlike the library-based version, this implementation avoids `numpy`, `scipy.stats`, and `pandas` for the core statistical computations. All algorithms are written manually using only:

- `math` — for elementary functions (`sqrt`, `log`, `exp`, `erf`, `pi`)
- `random` — for uniform random number generation
- `matplotlib` — **only** for plotting
- `scipy.special.gammainc` — **only** for the chi-square CDF (documented as a necessary exception, see below)

This approach demonstrates a deep understanding of the underlying mathematics behind random generation and goodness-of-fit tests.

---

## Objectives

- Model a **mixture of two Gaussian distributions** manually
- Implement the **Box–Muller transform** for normal random number generation
- Compute all **descriptive statistics** from scratch
- Implement the **Kolmogorov–Smirnov** test manually (including CDF and p-value approximation)
- Implement the **Pearson χ²** test manually (bins, merging, statistic, p-value)
- Build a **manual histogram** and plot it with theoretical densities
- Interpret results at significance level `α = 0.05`

---

## Project Structure

```
.
├── lab2_manual.py                # Main script (manual implementation)
├── task2_manual_histogram.png    # Graphical output
└── README.md                     # This file
```

---

## Requirements

- Python 3.8+
- `matplotlib`
- `scipy` (only for `scipy.special.gammainc`)

Install dependencies:

```bash
pip install matplotlib scipy
```

> **Note:** `numpy`, `pandas`, and `scipy.stats` are intentionally **not** used for the statistical logic.

---

## Task: Mixture of Two Gaussian Distributions

**Parameters (Variant 20):**

| Parameter | Value | Description |
|-----------|-------|-------------|
| μ₁ | 0 | Mean of first component |
| μ₂ | 6 | Mean of second component |
| σ₁ | 1 | Std. dev. of first component |
| α | 0.5 | Scale factor for σ₂ |
| σ₂ = α·σ₁ | 0.5 | Std. dev. of second component |
| ε | 0.45 | Mixing probability (contamination level) |
| n | 100 | Sample size |

**Generative model:**

For each observation `i = 1..n`:
1. Draw `u ~ U(0,1)`.
2. If `u < ε`, sample from `N(μ₂, σ₂²)`; otherwise sample from `N(μ₁, σ₁²)`.

---

## Manual Algorithms Implemented

### 1. Box–Muller Transform

Generates standard normal samples from two uniform variables:

$$z_1 = \sqrt{-2 \ln u_1} \cos(2\pi u_2), \quad z_2 = \sqrt{-2 \ln u_1} \sin(2\pi u_2)$$

Then transforms to `N(μ, σ²)` via `x = μ + σ·z`.

Two values are produced per pair of uniforms, improving efficiency.

### 2. Descriptive Statistics

All computed from first principles:

| Statistic | Formula |
|-----------|---------|
| Mean | `x̄ = (1/n) Σ xᵢ` |
| Variance | `s² = (1/(n−1)) Σ (xᵢ − x̄)²` |
| Std. dev. | `s = √s²` |
| Skewness | `(1/n) Σ ((xᵢ − x̄)/s)³` |
| Kurtosis | `(1/n) Σ ((xᵢ − x̄)/s)⁴ − 3` |

### 3. Normal CDF

Computed via the **error function**:

$$
F(x) = \frac{1}{2}\left[1 + \text{erf}\!\left(\frac{x-\mu}{\sigma\sqrt{2}}\right)\right]
$$

using `math.erf`.

### 4. Kolmogorov–Smirnov Test

- Empirical CDF: `Fₙ(xᵢ) = i/n` on sorted data.
- Theoretical CDF: `F(xᵢ)` via the formula above.
- Statistic: `D = max |Fₙ(xᵢ) − F(xᵢ)|`.
- P-value: Kolmogorov asymptotic series

$$Q(\lambda) = 2\sum_{k=1}^{\infty} (-1)^{k-1} e^{-2k^2\lambda^2}, \quad \lambda = \sqrt{n}\,D$$

(sum truncated at `k = 10`).

### 5. Pearson χ² Test

- Bins: 15 equal-width bins over `[min−pad, max+pad]` with 5% padding.
- Expected frequencies: `Eᵢ = n·(F(bᵢ₊₁) − F(bᵢ))`.
- **Automatic bin merging** while any `Eᵢ < 5`.
- Statistic: `χ² = Σ (Oᵢ − Eᵢ)² / Eᵢ`.
- Degrees of freedom: `df = k − 1 − 2` (two estimated parameters: `μ`, `σ`).
- P-value: `1 − F_χ²(χ²; df)`.

> **On the `gammainc` exception:** The chi-square CDF requires the **incomplete gamma function**, which has no closed form. A pure-Python implementation would need numerical integration (e.g., Simpson's rule on a non-integrable singular integrand) — both inefficient and fragile. `scipy.special.gammainc` is therefore used **only** as a numerical primitive, not as a statistical routine. All test logic (binning, merging, statistic, df) remains fully manual.

### 6. Manual Histogram

Bin edges and frequencies are computed explicitly in a Python loop, then converted to densities (`fᵢ / (n·w)`) so that the histogram integrates to 1 and can be compared with PDFs.

### 7. Density Functions

- Normal PDF: `φ(x) = (1/(σ√(2π)))·exp(−(x−μ)²/(2σ²))`
- Mixture PDF: `(1−ε)·φ₁(x) + ε·φ₂(x)`

---

## Expected Results

Since the sample comes from a **mixture** (bimodal, contaminated), the normality hypothesis should be **rejected** by both tests at `α = 0.05`.

| Criterion | Expected Outcome |
|-----------|------------------|
| K-S test | Reject H₀ |
| χ² test | Reject H₀ |
| Skewness | Positive (right tail from 2nd component) |
| Kurtosis | Negative (platykurtic, bimodal shape) |

The histogram will show a clear **two-peak structure** that no single Gaussian can fit, while the true mixture PDF follows the data closely.

---

## Usage

Run the analysis:

```bash
python lab2_manual.py
```

**Output:**
- Descriptive statistics table (printed to console)
- K-S test statistic and p-value
- χ² test statistic, degrees of freedom, and p-value
- Interpretation at `α = 0.05`
- Saved figure: `task2_manual_histogram.png`

---

## Graphical Output

The generated figure contains:

| Element | Style |
|---------|-------|
| Histogram (density-normalized) | Blue bars |
| Fitted single-Gaussian PDF | Red solid line |
| True two-component mixture PDF | Green dashed line |

The visual gap between the red curve (single Gaussian) and the data confirms the rejection of normality, while the green curve (true mixture) matches the histogram.

---

## Reference

- Харин Ю. С., Абрамович М. С., Малюгин В. И., Харин А. Ю.  
  *Компьютерный анализ данных. Статистические модели и методы.*  
  БГУ, Минск, 2025. — [elib.bsu.by](https://elib.bsu.by/handle/123456789/341249)

---

## Notes

- Random seed is fixed (`random.seed(1)`) for reproducibility.
- The Box–Muller generator produces samples in pairs; the last odd sample is handled correctly.
- Bin merging in the χ² test is iterative and handles both left and right edge cases.
- Task 3 is not implemented (marked as *"to be continued"* in the assignment).

---

## Summary

| Aspect | Implementation |
|--------|----------------|
| Normal generation | Box–Muller (manual) |
| Descriptive statistics | All manual |
| Normal CDF | `math.erf` |
| K-S test | Manual (CDF, statistic, p-value) |
| χ² test | Manual (binning, merging, statistic) |
| χ² CDF | `scipy.special.gammainc` (numerical primitive only) |
| Histogram | Manual binning |
| Plotting | `matplotlib` |