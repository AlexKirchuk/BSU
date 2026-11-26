from numpy.typing import NDArray
from sklearn.linear_model import SGDRegressor


class OnlineRegressor:
    def __init__(
        self,
        learning_rate: float = 0.01,
        random_state: int = 42
    ) -> None:
        self.model = SGDRegressor(
            loss="squared_error",
            penalty=None,
            learning_rate="constant",
            eta0=learning_rate,
            random_state=random_state
        )

        self.is_fitted = False

    def predict(self, X: NDArray) -> NDArray:
        if not self.is_fitted:
            raise RuntimeError("Model has not been fitted yet.")

        return self.model.predict(X)

    def update(self, X: NDArray, y: NDArray) -> None:
        self.model.partial_fit(X, y)
        self.is_fitted = True
