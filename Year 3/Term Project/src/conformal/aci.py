from collections import deque
from math import ceil

import numpy as np


class ACICalibrator:
    def __init__(
        self,
        alpha: float = 0.1,
        gamma: float = 0.01,
        window_size: int = 100,
        min_alpha: float = 0.001,
        max_alpha: float = 0.999
    ) -> None:
        if not 0 < alpha < 1:
            raise ValueError("Alpha must be between 0 and 1.")

        if gamma <= 0:
            raise ValueError("Gamma must be positive.")

        if window_size < 1:
            raise ValueError("Window size must be positive.")

        self.target_alpha = alpha
        self.current_alpha = alpha
        self.gamma = gamma

        self.min_alpha = min_alpha
        self.max_alpha = max_alpha

        self.scores = deque(maxlen=window_size)

    def get_quantile(self) -> float:
        n = len(self.scores)

        if n == 0:
            return float("inf")

        k = ceil((n + 1) * (1 - self.current_alpha))

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

        if not np.isfinite(lower) or not np.isfinite(upper):
            return

        miss = float(y_true < lower or y_true > upper)

        self.current_alpha += self.gamma * (
                self.target_alpha - miss
        )

        self.current_alpha = float(
            np.clip(
                self.current_alpha,
                self.min_alpha,
                self.max_alpha
            )
        )
