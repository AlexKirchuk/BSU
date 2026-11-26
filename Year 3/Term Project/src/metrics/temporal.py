import numpy as np


def calculate_rolling_coverage(
    y_true: np.ndarray,
    lower_bounds: np.ndarray,
    upper_bounds: np.ndarray,
    window_size: int = 20
) -> np.ndarray:
    if window_size < 1:
        raise ValueError("Window size must be positive.")

    covered = (
        (y_true >= lower_bounds)
        & (y_true <= upper_bounds)
    ).astype(float)

    if len(covered) < window_size:
        return np.array([], dtype=float)

    return np.convolve(
        covered,
        np.ones(window_size) / window_size,
        mode="valid"
    )



def calculate_recovery_time(
    rolling_coverage: np.ndarray,
    indices: np.ndarray,
    change_point: int,
    target_coverage: float = 0.9
) -> int | None:
    window_size = len(indices) - len(rolling_coverage) + 1

    if window_size < 1:
        return None

    for start_position, coverage in enumerate(rolling_coverage):
        end_position = start_position + window_size - 1

        window_start = indices[start_position]
        window_end = indices[end_position]

        # Ignore windows containing observations from before the drift.
        if window_start < change_point:
            continue

        if coverage >= target_coverage:
            return int(window_end - change_point)

    return None
