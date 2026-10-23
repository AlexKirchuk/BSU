# Laboratory Work 1: Statistical Goodness-of-Fit Tests

## Overview

This repository contains the implementation of **Laboratory Work 1** on statistical goodness-of-fit tests. The work covers modeling random samples, testing them for normality using classical statistical criteria, and performing descriptive analysis.

The implementation is done in **Python** using standard scientific libraries (`numpy`, `scipy`, `pandas`, `matplotlib`, `seaborn`).

---

## Objectives

- Model random samples from a normal distribution
- Model a mixture of two Gaussian distributions
- Verify the conformity of simulated data to the normal distribution using:
  - **Kolmogorov–Smirnov test**
  - **Pearson's chi-squared (χ²) test**
- Compute descriptive statistics (mean, variance, std. deviation, min, max, skewness, kurtosis)
- Perform graphical analysis of the results

---

## Project Structure

```
.
├── lab1.py                  # Main script with all computations
├── task2_histogram.png      # Graphical output for Task 2
└── README.md                # This file
```

---

## Requirements

- Python 3.8+
- `numpy`
- `scipy`
- `pandas`
- `matplotlib`
- `seaborn`

Install dependencies:

```bash
pip install numpy scipy pandas matplotlib seaborn
```

---

## Task 1: Normal Distribution

**Parameters:**
- Sample size: `n = 300`
- Distribution: `N(μ, σ²)` with `μ = 0`, `σ² = 20`

**Steps:**
1. Generate a random sample from the normal distribution.
2. Compute descriptive statistics.
3. Perform **Kolmogorov–Smirnov** test (standardized sample vs. standard normal).
4. Perform **Pearson χ²** test with automatic bin merging for expected frequencies `< 5`.
5. Interpret results at significance level `α = 0.05`.

**Expected outcome:** The sample follows a normal distribution (fail to reject H₀).

---

## Task 2: Mixture of Two Gaussian Distributions

**Parameters (Variant 20):**
| Parameter | Value |
|-----------|-------|
| μ₁ | 0 |
| μ₂ | 6 |
| σ₁ | 1 |
| σ₂ = α·σ₁ | 0.5 |
| α | 0.5 |
| ε (mixing level) | 0.45 |
| n | 100 |

**Modeling:**
For each observation, with probability `ε` sample from `N(μ₂, σ₂²)`, otherwise from `N(μ₁, σ₁²)`.

**Steps:**
1. Simulate the mixture sample.
2. Compute descriptive statistics.
3. Apply Kolmogorov–Smirnov and χ² tests (with automatic bin merging).
4. Build a histogram with:
   - Fitted normal PDF
   - True mixture PDF
5. Interpret results.

**Expected outcome:** The data **does not** follow a single normal distribution (mixture has bimodal shape, positive skewness).

---

## Statistical Tests Used

### Kolmogorov–Smirnov Test
Compares the empirical CDF with the theoretical normal CDF. The sample is standardized before testing:

$$z_i = \frac{x_i - \bar{x}}{s}$$

### Pearson's χ² Test
Compares observed and expected frequencies across bins. Bins with expected frequency `< 5` are merged iteratively. Degrees of freedom are adjusted: `df = k − 1 − 2` (two estimated parameters: μ and σ).

---

## Graphical Analysis

The script produces `task2_histogram.png` containing:
- Histogram of the mixture sample (density-normalized)
- Fitted single-Gaussian PDF (red solid line)
- True two-component mixture PDF (green dashed line)

This visualization clearly shows why the normality hypothesis is rejected for the mixture.

---

## Usage

Run the full analysis:

```bash
python lab1.py
```

The script prints:
- Descriptive statistics tables
- Test statistics and p-values
- Interpretation of hypotheses at `α = 0.05`
- A comparative summary table
- Saves the graphical output as `task2_histogram.png`

---

## Reference

- Харин Ю. С., Абрамович М. С., Малюгин В. И., Харин А. Ю.  
  *Компьютерный анализ данных. Статистические модели и методы.*  
  БГУ, Минск, 2025. — [elib.bsu.by](https://elib.bsu.by/handle/123456789/341249)

---

## Notes

- Task 3 is marked as *"to be continued"* in the assignment and is not implemented in this version.
- Random seeds are fixed (`seed = 1` for Task 1, `seed = 2` for Task 2) to ensure reproducibility.
- The χ² test uses a manual p-value calculation based on the chi-square CDF to correctly account for estimated parameters.

---

## Results Summary

| Criterion | Task 1 (Normal) | Task 2 (Mixture) |
|-----------|-----------------|------------------|
| K-S test | H₀ not rejected | H₀ rejected |
| χ² test | H₀ not rejected | H₀ rejected |
| Conclusion | Normal | Not normal |