# Laboratory Work 4: Stationary Random Processes

## Overview

This repository contains a from-scratch (manual) implementation of
Laboratory Work 4 (continuation of Lab 3), Tasks 2-3:

- Task 2: ensemble averaging of the sample covariance function and
  construction of a 95% confidence interval;
- Task 3: computer simulation of the random walk process according to
  Section 3.4 of the textbook.

The implementation intentionally avoids high-level statistical routines for
the core logic: all ensemble statistics, standard errors, confidence
intervals, and the random-walk generator are implemented manually using only:

- numpy       - for arrays and vectorized arithmetic
- math        - for elementary functions (sqrt, log, exp, pi)
- matplotlib  - only for plotting
- scipy.stats - only for reference (not used in the core logic of Tasks 2-3)

This approach demonstrates a deep understanding of the underlying mathematics
behind ensemble averaging, confidence intervals, and random-walk modeling.

---

## Objectives

Task 2:
- Simulate m = 100 independent realizations of the AR(2) process from Lab 3,
  each of length n = 150
- Compute the sample covariance function R_tilde_k(h) for each realization
- Average the covariance function over the ensemble:
  R_bar(h) = (1/m) * sum_k R_tilde_k(h)
- Compute the corrected sample standard deviation s_R(h) and standard error
  SE(h) = s_R(h) / sqrt(m)
- Construct the 95% confidence interval R_bar(h) +- 1.96 * SE(h)
- Plot the theoretical covariance, ensemble mean, and confidence interval
  for h = 0, ..., 30

Task 3:
- Simulate the random walk process xi_t according to Section 3.4 of the
  textbook
- Use the inverse transform method (Section 1.3) to generate increments
  eta_t in {-delta, 0, delta}
- Verify the asymptotic property Var[xi_t] -> b^2 * t as Delta -> 0
- Demonstrate the nonstationarity of the process

---

## Project Structure

```
.
├── main.py                       # Main script (manual implementation)
└── README.md                     # This file
```

---

## Requirements

- Python 3.8+
- numpy
- matplotlib
- scipy (only for reference; not used in the core logic of Tasks 2-3)

Install dependencies:

    pip install numpy matplotlib scipy

---

## Task 2: Ensemble Averaging of the Covariance Function

Parameters (Variant 4, inherited from Lab 3):

| Parameter | Value | Description              |
|-----------|-------|--------------------------|
| mu        | 0     | Mean of the process      |
| D = R(0)  | 2.0   | Variance                 |
| alpha     | 0.4   | Decay rate               |
| beta      | 1.2   | Oscillation frequency    |
| Delta     | 1.0   | Discretization step      |
| n         | 150   | Sample size              |
| m         | 100   | Number of realizations   |

Simulation: AR(2) exact discretization (same as in Lab 3):

    rho    = exp(-alpha*Delta)
    phi1   = 2*rho*cos(beta*Delta)
    phi2   = -rho^2
    X_k    = phi1*X_{k-1} + phi2*X_{k-2} + sigma*eta_k,  eta_k ~ N(0,1)
    sigma^2 = D * (1+phi2)*((1-phi2)^2 - phi1^2) / (1-phi2)

Estimators:

    R_tilde_k(h) = 1/(n-h) * sum_{s=1}^{n-h} (X_k(s+h) - mu_bar_k)(X_k(s) - mu_bar_k)
    R_bar(h)     = (1/m) * sum_{k=1}^{m} R_tilde_k(h)
    s_R(h)       = sqrt( (1/(m-1)) * sum_{k=1}^{m} (R_tilde_k(h) - R_bar(h))^2 )
    SE(h)        = s_R(h) / sqrt(m)
    CI_95(h)     = R_bar(h) +- 1.96 * SE(h)

Plot (Fig. 1): Theoretical R(h), ensemble mean R_bar(h), and 95% CI
for h = 0, ..., 30.

---

## Task 3: Random Walk Simulation (Section 3.4)

Model (textbook, Section 3.4):

- Discrete time t = m*Delta, m = 0, 1, 2, ..., step Delta > 0
- Discrete state space xi_t in {x = l*delta : l = 0, +-1, +-2, ...}, step delta > 0
- Initial state xi_0 = 0
- Increments eta_t in {-delta, 0, delta} independent with probabilities

    P{eta_t = +-delta} = p_pm,
    P{eta_t = 0}       = 1 - p_+ - p_-

- Process equation:

    xi_{t+Delta} = xi_t + eta_t,  t = 0, Delta, 2Delta, ...

Asymptotics as Delta -> 0:

    delta = b*sqrt(Delta) + o(sqrt(Delta))
    p_pm  = 1/2 +- a/(2b)*sqrt(Delta) + o(sqrt(Delta))

where b > 0 is the diffusion coefficient and a in R^1 is the drift
coefficient. For a = 0, b = 1 the limit is the standard Wiener process w_t.

Generation of increments: inverse transform method (Section 1.3):

- Draw U ~ U(0,1)
- If U < p_+                 -> eta_t = +delta
- If p_+ <= U < p_+ + p_0    -> eta_t = 0
- If U >= p_+ + p_0          -> eta_t = -delta

Simulation parameters:

| Parameter       | Value |
|-----------------|-------|
| Delta           | 0.01  |
| b               | 1.0   |
| a               | 0.0   |
| delta = b*sqrt(Delta) | 0.1 |
| p_+ = p_-       | 0.5   |
| p_0             | 0.0   |
| N               | 1000  |
| t_max = N*Delta | 10.0  |
| Number of trajectories | 5 (+ 200 for variance check) |

Plot (Fig. 2): 5 random-walk trajectories with the theoretical
+-1.96*sqrt(b^2*t) corridor.

Verification: the empirical variance of the ensemble is compared with b^2*t
at t = 1, 2, 5, 10.

---

## Expected Results

Task 2:

| Criterion          | Expected Outcome                                |
|--------------------|-------------------------------------------------|
| R_bar(0)           | Close to R(0) = 2.0                             |
| Shape of R_bar(h)  | Exponential decay + oscillations, alpha=0.4, beta=1.2 |
| s_R(h)             | Smallest at h = 0, grows with h                 |
| 95% CI             | Contains R(h) for the majority of lags          |
| Effect of averaging| Variance of the estimator reduced by sqrt(m)=10 |

Task 3:

| Criterion          | Expected Outcome                                |
|--------------------|-------------------------------------------------|
| Trajectories       | Nonstationary, no mean reversion                |
| Variance           | Grows linearly with t: Var[xi_t] ~= b^2 * t     |
| Sample covariance  | Does not decay with lag (nonstationary)         |
| Limit as Delta->0  | Standard Wiener process w_t                     |

---

## Usage

Run the analysis:

    python lab4_tasks2_3.py

Output:
- Task 2: full table of R_th(h), R_bar(h), s_R(h), SE(h), lower and upper
  CI bounds for h = 0, ..., 30
- Task 2: number of lags where R_th(h) falls inside the 95% CI
- Task 3: simulation parameters Delta, b, a, delta, p_pm, p_0
- Task 3: variance check table
- Task 3: sample covariance of one trajectory
- Conclusions for both tasks printed to the console
- Saved figures: fig1_covariance_ci.png, fig2_random_walk.png

---

## Graphical Output

| Figure | Content                                                     |
|--------|-------------------------------------------------------------|
| Fig. 1 | Theoretical R(h), ensemble mean R_bar(h), 95% CI (h = 0..30)|
| Fig. 2 | Random-walk trajectories xi_t with +-1.96*sqrt(b^2*t) corridor |

---

## Reference

Kharin Yu. S., Abramovich M. S., Malyugin V. I., Kharin A. Yu.
Computer Data Analysis. Statistical Models and Methods.
BSU, Minsk, 2025. - https://elib.bsu.by/handle/123456789/341249

---

## Notes

- Random seeds are fixed for reproducibility: default_rng(52375) for Task 2,
  default_rng(2026) for Task 3.
- Task 2 uses the same AR(2) algorithm as in Lab 3, so the results are
  consistent with the earlier work.
- Task 3 reproduces the random walk exactly as defined in Section 3.4 of the
  textbook: increments eta_t in {-delta, 0, delta}, initial state xi_0 = 0,
  and the recurrence xi_{t+Delta} = xi_t + eta_t.
- The a = 0, b = 1 choice corresponds to the standard Wiener process; other
  parameter values can be plugged in without changing the code structure.

---

## Summary

| Aspect                  | Implementation                                  |
|-------------------------|-------------------------------------------------|
| Task 2 simulation       | AR(2) exact discretization, m = 100 realizations|
| Ensemble mean           | Manual formula                                  |
| Standard error          | Manual: s_R / sqrt(m)                           |
| Confidence interval     | Manual: R_bar +- 1.96 * SE                      |
| Task 3 simulation       | Random walk from Section 3.4                    |
| Increment generation    | Inverse transform method (Section 1.3)          |
| Variance verification   | Empirical variance vs b^2 * t                   |
| Plotting                | matplotlib                                      |