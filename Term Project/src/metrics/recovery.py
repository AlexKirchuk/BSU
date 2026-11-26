import numpy as np


def aggregate_recovery_times(records: list[dict]) -> dict:
    values = [
        record["recovery_time"]
        for record in records
        if record["recovery_time"] is not None
    ]

    recovery_rate = len(values) / len(records) if records else 0.0

    if not values:
        return {
            "recovery_rate": recovery_rate,
            "mean_recovery_time": None,
            "median_recovery_time": None,
            "std_recovery_time": None
        }

    values = np.asarray(values, dtype=float)

    return {
        "recovery_rate": float(recovery_rate),
        "mean_recovery_time": float(np.mean(values)),
        "median_recovery_time": float(np.median(values)),
        "std_recovery_time": float(np.std(values, ddof=1))
        if len(values) > 1 else 0.0
    }
