# Laboratory Work 3: Stationary Random Processes (Task 1)

## Overview

This repository contains a from-scratch (manual) implementation of Laboratory
Work 3, Task 1 on modeling and analyzing a stationary Gaussian random process
with a given covariance function (Variant 4).

The implementation intentionally avoids high-level statistical routines for the
core logic: all descriptive statistics, the covariance estimator, the Q-Q
analysis, and the trend diagnostics are implemented manually using only:

- numpy       - for arrays and vectorized arithmetic
- math        - for elementary functions (sqrt, log, exp, pi, erf)
- matplotlib  - only for plotting
- scipy.stats - only for reference goodness-of-fit tests (K-S, Shapiro-Wilk)

This approach demonstrates a deep understanding of the underlying mathematics
behind AR(2) simulation and preliminary statistical analysis.

---

## Objectives

- Model a stationary Gaussian process with a given covariance function (Variant 4)
- Choose and justify an AR(2) simulation algorithm based on exact discretization
- Compute all descriptive statistics from first principles
- Build a histogram and overlay the fitted normal density
- Perform homogeneity analysis without statistical tests
- Detect outliers using the Hampel rule (no formal tests)
- Build a box-and-whisker plot
- Analyze the distribution law via a normal probability plot and goodness-of-fit tests
- Perform a visual trend analysis
- Compute the sample covariance function and compare it with the theoretical one

---

## Project Structure

.
├── lab3_task1.py                 # Main script
├── fig1_realization.png          # Realization X(t)
├── fig2_histogram.png            # Histogram + fitted N(mean, std)
├── fig3_boxplot.png              # Box-and-whisker plot
├── fig4_qq.png                   # Normal probability plot
├── fig5_trend.png                # Trend analysis
├── fig6_covariance.png           # R(h) and R_hat(h)
└── README.md                     # This file

---

## Requirements

- Python 3.8+
- numpy
- matplotlib
- scipy

Install dependencies:

    pip install numpy matplotlib scipy

---

## Task: Stationary Gaussian Process (Variant 4)

Parameters (Variant 4):

| Parameter | Value | Description              |
|-----------|-------|--------------------------|
| mu        | 0     | Mean of the process      |
| D = R(0)  | 2.0   | Variance                 |
| alpha     | 0.4   | Decay rate               |
| beta      | 1.2   | Oscillation frequency    |
| Delta     | 1.0   | Discretization step      |
| n         | 150   | Sample size              |

Covariance function:

    R(t) = D * exp(-alpha*|t|) * (cos(beta*t) - (alpha/beta)*sin(beta*|t|)),
    D, alpha, beta > 0.

Spectral density: rational, which makes the process an AR(2) process after
exact discretization.

---

## Manual Algorithms Implemented

### 1. AR(2) Simulation (Exact Discretization)

The process is simulated as an AR(2) process with coefficients derived from
the continuous-time covariance function:

    rho    = exp(-alpha*Delta)
    phi1   = 2*rho*cos(beta*Delta)
    phi2   = -rho^2
    X_k    = phi1*X_{k-1} + phi2*X_{k-2} + sigma*eta_k,  eta_k ~ N(0,1)
    sigma^2 = D * (1+phi2)*((1-phi2)^2 - phi1^2) / (1-phi2)

The stationarity condition |phi1| + |phi2| < 1 holds for all alpha, beta > 0.
A warm-up of 100 samples is used before the working segment of n = 150
observations.

### 2. Descriptive Statistics

All computed from first principles:

| Statistic  | Formula                              |
|------------|--------------------------------------|
| Mean       | x_bar = (1/n) * sum(x_i)             |
| Variance   | s^2   = (1/(n-1)) * sum((x_i - x_bar)^2) |
| Std. dev.  | s     = sqrt(s^2)                    |
| Skewness   | (1/n) * sum(((x_i - x_bar)/s)^3)     |
| Kurtosis   | (1/n) * sum(((x_i - x_bar)/s)^4) - 3 |
| Quartiles  | Q1, Q3 via numpy.percentile          |

### 3. Histogram

Bin edges and frequencies are computed explicitly, then normalized to
densities so that the histogram integrates to 1 and can be compared with
PDFs. The fitted normal density N(x_bar, s^2) is overlaid.

### 4. Homogeneity Analysis (No Tests)

Descriptive comparison of the two halves of the sample:
- mean of the first half vs mean of the second half
- variance of the first half vs variance of the second half

### 5. Outlier Detection (Hampel Rule)

A descriptive heuristic, not a significance test. An observation is flagged
if it falls outside

    [x_med - 5.2 * x_mad ; x_med + 5.2 * x_mad]

where x_med is the sample median and x_mad is the median absolute deviation.

### 6. Box-and-Whisker Plot

Built with matplotlib.boxplot; the box spans [Q1, Q3], the median is marked
in red, and the whiskers extend to +-1.5*(Q3 - Q1).

### 7. Normal Probability Plot and Goodness-of-Fit Tests

- Q-Q plot via scipy.stats.probplot
- Kolmogorov-Smirnov test
- Shapiro-Wilk test

Both tests are applied at alpha = 0.05.

### 8. Trend Analysis (Visual)

- The realization is compared with its moving average (window w = 7) and
  with the linear regression X_t = a + b*t.
- The significance of the slope b is checked via its p-value.

### 9. Sample Covariance Function

The estimator from the assignment is implemented exactly:

    R_bar(h) = 1/(n-h) * sum_{s=1}^{n-h} (X(s+h) - mu_bar)(X(s) - mu_bar),
    h = 0, ..., n-1,
    mu_bar   = 1/n * sum_{j=1}^{n} X(j),
    R_bar(-h) = R_bar(h), R_bar(h) = 0 for |h| >= n.

The estimate is compared with the theoretical R(h) on h = 0, ..., 2n/3 = 100.

---

## Expected Results

The simulated series comes from a stationary Gaussian process, so:

| Criterion          | Expected Outcome                                  |
|--------------------|---------------------------------------------------|
| Mean               | Close to mu = 0                                   |
| Variance           | Close to D = 2.0                                  |
| Histogram          | Unimodal, symmetric, close to N(0, 2)             |
| Q-Q plot           | Points near the diagonal                          |
| K-S / Shapiro-Wilk | Do not reject normality at alpha = 0.05           |
| Hampel rule        | No outliers (clean Gaussian sample)               |
| Homogeneity        | Two halves have similar mean and variance         |
| Trend              | Slope statistically insignificant                 |
| Covariance         | R_bar(0) ~= R(0) = 2.0, curves coincide           |

---

## Usage

Run the analysis:

    python lab3_task1.py

Output:
- AR(2) coefficients and stationarity check (printed to console)
- Descriptive statistics table
- Hampel rule interval and detected outliers
- K-S and Shapiro-Wilk test results
- Linear trend fit (slope, p-value)
- Comparison of R_bar(0) with R(0)
- Saved figures: fig1_realization.png ... fig6_covariance.png

---

## Graphical Output

| Figure | Content                                          |
|--------|--------------------------------------------------|
| Fig. 1 | Realization X(t), n = 150                        |
| Fig. 2 | Histogram + fitted normal density                |
| Fig. 3 | Box-and-whisker plot                             |
| Fig. 4 | Normal probability plot (Q-Q)                    |
| Fig. 5 | Realization + moving average + linear trend      |
| Fig. 6 | Theoretical R(h) and estimate R_bar(h), h = 0..100 |

---

## Reference

Kharin Yu. S., Abramovich M. S., Malyugin V. I., Kharin A. Yu.
Computer Data Analysis. Statistical Models and Methods.
BSU, Minsk, 2025. - https://elib.bsu.by/handle/123456789/341249

---

## Notes

- Random seed is fixed (numpy.random.default_rng(52375)) for reproducibility.
- AR(2) warm-up of 100 samples ensures stationarity of the working segment.
- The Hampel rule uses the factor 5.2 as a descriptive heuristic (not a
  significance test).
- The covariance estimate is computed for lags h = 0, ..., 100 per the
  assignment.

---

## Summary

| Aspect               | Implementation                          |
|----------------------|-----------------------------------------|
| Process simulation   | AR(2) exact discretization              |
| Descriptive statistics | Manual / numpy                        |
| Histogram            | matplotlib.hist with density normalization |
| Homogeneity          | Descriptive comparison of halves        |
| Outliers             | Hampel rule (5.2 * MAD)                 |
| Boxplot              | matplotlib.boxplot                      |
| Q-Q plot             | scipy.stats.probplot                    |
| Goodness-of-fit      | K-S, Shapiro-Wilk                       |
| Trend analysis       | Moving average + linear regression      |
| Covariance estimate  | Manual formula from the assignment      |
| Plotting             | matplotlib                              |