import numpy as np

from src.conformal.aci import ACICalibrator
from src.conformal.sliding_window import SlidingWindowCalibrator
from src.models.online_regressor import OnlineRegressor


def run_online_experiment(
    X: np.ndarray,
    y: np.ndarray,
    method: str = "sliding_window",
    alpha: float = 0.1,
    gamma: float = 0.01,
    window_size: int = 100,
    warmup_size: int = 100
) -> dict:
    model = OnlineRegressor()

    if method == "sliding_window":
        calibrator = SlidingWindowCalibrator(
            alpha=alpha,
            window_size=window_size
        )
    elif method == "aci":
        calibrator = ACICalibrator(
            alpha=alpha,
            gamma=gamma,
            window_size=window_size
        )
    else:
        raise ValueError(f"Unknown calibration method: {method}")

    predictions = []
    lower_bounds = []
    upper_bounds = []
    actual_values = []
    indices = []
    alpha_history = []

    for i in range(len(X)):
        X_current = X[i:i + 1]
        y_current = float(y[i])

        if not model.is_fitted:
            model.update(X_current, np.array([y_current]))
            continue

        prediction = float(model.predict(X_current)[0])

        if len(calibrator.scores) < warmup_size:
            lower, upper = -np.inf, np.inf
        else:
            lower, upper = calibrator.get_interval(prediction)

        predictions.append(prediction)
        lower_bounds.append(lower)
        upper_bounds.append(upper)
        actual_values.append(y_current)
        indices.append(i)

        calibrator.update(
            y_true=y_current,
            y_pred=prediction,
            lower=lower,
            upper=upper
        )

        if method == "aci":
            alpha_history.append(calibrator.current_alpha)

        model.update(X_current, np.array([y_current]))

    return {
        "predictions": np.asarray(predictions),
        "lower_bounds": np.asarray(lower_bounds),
        "upper_bounds": np.asarray(upper_bounds),
        "actual_values": np.asarray(actual_values),
        "indices": np.asarray(indices),
        "alpha_history": np.asarray(alpha_history),
        "evaluation_start": warmup_size
    }
