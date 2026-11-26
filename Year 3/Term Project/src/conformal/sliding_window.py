from collections import deque
from math import ceil

import numpy as np


class SlidingWindowCalibrator:
    def __init__(
        self,
        alpha: float = 0.1,
        window_size: int = 100
    ) -> None:
        if not 0 < alpha < 1:
            raise ValueError("Alpha must be between 0 and 1.")

        if window_size < 1:
            raise ValueError("Window size must be positive.")

        self.alpha = alpha
        self.window_size = window_size
        self.scores = deque(maxlen=window_size)

    def get_quantile(self) -> float:
        n = len(self.scores)

        if n == 0:
            return float("inf")

        k = ceil((n + 1) * (1 - self.alpha))

        if k > n:
            return float("inf")

        scores = np.sort(np.asarray(self.scores))

        return float(scores[k - 1])

    def get_interval(
        self,
        y_pred: float
    ) -> tuple[float, float]:
        q = self.get_quantile()

        return y_pred - q, y_pred + q

    def update(
        self,
        y_true: float,
        y_pred: float,
        lower: float,
        upper: float
    ) -> None:
        score = abs(y_true - y_pred)
        self.scores.append(score)
