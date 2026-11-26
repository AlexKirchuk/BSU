import numpy as np


def calculate_metrics(
    y_true: np.ndarray,
    predictions: np.ndarray,
    lower_bounds: np.ndarray,
    upper_bounds: np.ndarray
) -> dict:
    covered = (
        (y_true >= lower_bounds)
        & (y_true <= upper_bounds)
    )

    coverage = np.mean(covered)
    mae = np.mean(np.abs(y_true - predictions))
    width = np.mean(upper_bounds - lower_bounds)

    return {
        "coverage": float(coverage),
        "average_width": float(width),
        "mae": float(mae)
    }
