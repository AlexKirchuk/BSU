# Online Models with Guaranteed Coverage

## Overview

This project explores **online regression models with adaptive prediction intervals** and evaluates their ability to maintain a predefined prediction coverage level under different data conditions.

The implementation combines an online regression model based on `SGDRegressor` with two conformal calibration strategies:

- **Sliding Window** — estimates the prediction interval using recent prediction errors stored in a fixed-size window.
- **Adaptive Conformal Inference (ACI)** — dynamically adjusts the miscoverage level based on whether previous predictions fell outside their intervals.

The main objective is to compare these approaches in terms of empirical coverage, prediction interval width, and adaptation to changes in the data distribution.

## Key Features

- Online regression with incremental model updates using `partial_fit`.
- Prediction intervals based on absolute residual scores.
- Sliding Window conformal calibration.
- Adaptive Conformal Inference with an adjustable miscoverage level.
- Synthetic data generation for different distribution scenarios.
- Repeated experiments for more reliable result aggregation.
- Evaluation of coverage, interval width, prediction error, and adaptation time.
- Visualization and export of experimental results.

## Methods

### Online Regression

The project uses `SGDRegressor` from Scikit-learn as the base regression model.

Unlike traditional batch training, the model is updated incrementally as new observations arrive. At each step, it first generates a prediction and then updates its parameters using the newly received observation.

### Sliding Window Calibration

This method stores recent absolute prediction errors in a fixed-size window.

The calibration quantile is calculated from the stored residuals and used to construct a prediction interval:

$$
C_t(x_t) =
[\hat{y}_t - q_t,\ \hat{y}_t + q_t]
$$

where:

- $\hat{y}_t$ is the model prediction;
- $q_t$ is the calibration quantile estimated from recent residuals.

Older observations are gradually removed from the window, allowing the calibration mechanism to adapt to recent changes.

### Adaptive Conformal Inference (ACI)

ACI dynamically adjusts the current miscoverage level according to the prediction result.

The update rule is:

$$
\alpha_{t+1}
=
\alpha_t + \gamma(\alpha - E_t)
$$

where:

- $\alpha$ is the target miscoverage level;
- $\alpha_t$ is the current adaptive miscoverage level;
- $\gamma$ is the adaptation rate;
- $E_t$ equals 1 if the observation falls outside the prediction interval and 0 otherwise.

This mechanism increases the interval's potential width after a missed prediction and adjusts it in the opposite direction after a successful prediction.

## Experimental Scenarios

Three synthetic data scenarios are used to evaluate the calibration methods.

| Scenario | Description |
|---|---|
| Stationary Data | The underlying relationship between input features and target values remains constant. |
| Changing Variance | The variance of the observation noise increases with the input feature. |
| Concept Drift | The underlying regression function changes during the data stream. |

Each scenario contains 1,000 observations. The experiments are repeated 30 times to evaluate the stability of the results.

The target coverage level is set to **90%**.

## Evaluation Metrics

The following metrics are used to compare the methods:

- **Empirical Coverage** — the proportion of actual target values contained within their prediction intervals.
- **Average Interval Width** — the average difference between the upper and lower interval bounds.
- **Mean Absolute Error (MAE)** — the average absolute difference between predicted and actual values.
- **Recovery Time** — the number of observations required for rolling coverage to return to the target level after a distribution change.

## Experimental Results

The experiments demonstrate that both calibration methods achieve empirical coverage close to the target level in the tested scenarios.

| Scenario | Method | Coverage | Average Width | MAE |
|---|---|---:|---:|---:|
| Stationary | Sliding Window | 90.66% | 8.07 | 1.91 |
| Stationary | ACI | 90.01% | 8.00 | 1.91 |
| Changing Variance | Sliding Window | 90.12% | 13.61 | 2.99 |
| Changing Variance | ACI | 90.01% | 13.79 | 2.99 |
| Concept Drift | Sliding Window | 90.64% | 8.14 | 1.94 |
| Concept Drift | ACI | 90.01% | 8.08 | 1.94 |

The results show that:

- Both methods maintain coverage close to the desired 90% level.
- ACI produces coverage particularly close to the target across all three scenarios.
- Sliding Window produces slightly narrower intervals in the changing-variance scenario.
- The underlying regression model is shared between the calibration methods, so their MAE values are identical within each scenario.

The experiments also show that both methods successfully recovered their target rolling coverage after the simulated concept drift in all 30 runs.

*Note: These are empirical results obtained on synthetic data. They should not be interpreted as a universal theoretical coverage guarantee under arbitrary distribution shifts.*

## Project Structure

```text
online-models-coverage/
├── src/
│   ├── data/
│   │   └── generator.py
│   ├── models/
│   │   └── online_regressor.py
│   ├── conformal/
│   │   ├── sliding_window.py
│   │   └── aci.py
│   ├── metrics/
│   │   ├── evaluation.py
│   │   ├── aggregation.py
│   │   ├── temporal.py
│   │   └── recovery.py
│   ├── experiments/
│   │   ├── online_experiment.py
│   │   ├── runner.py
│   │   ├── export.py
│   │   └── temporal_export.py
│   └── visualization/
│       └── plots.py
├── results/
├── main.py
├── plot_results.py
└── requirements.txt
```

## Technologies

- **Python** — primary programming language.
- **NumPy** — numerical computations and synthetic data generation.
- **Scikit-learn** — online regression model.
- **Matplotlib** — visualization of experimental results.

## Installation

Clone the repository:

```bash
git clone <repository-url>
cd online-models-coverage
```

Create and activate a virtual environment:

```bash
python -m venv .venv
```

On Windows:

```bash
.venv\Scripts\activate
```

On Linux and macOS:

```bash
source .venv/bin/activate
```

Install dependencies:

```bash
pip install -r requirements.txt
```

## Running the Project

Run the experiments:

```bash
python main.py
```

Generate visualizations from the exported results:

```bash
python plot_results.py
```

The generated experimental data and plots are stored in the `results/` directory.

## Limitations

- The experiments use synthetic datasets rather than real-world data.
- The quality of online adaptation depends on calibration window size and ACI learning rate.
- Empirical coverage on the tested data does not establish a universal guarantee for arbitrary non-stationary distributions.
- The current implementation focuses on regression and symmetric prediction intervals.

## Conclusion

This project provides an experimental implementation of online regression with conformal prediction intervals.

By comparing Sliding Window calibration and Adaptive Conformal Inference, it demonstrates how different calibration strategies behave under stationary conditions, changing noise variance, and concept drift.

The results highlight the trade-off between maintaining the target coverage level and producing narrower prediction intervals.