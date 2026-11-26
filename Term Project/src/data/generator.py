import numpy as np


def generate_stationary_data(
    n_samples: int = 1000,
    noise_std: float = 2.0,
    random_state: int = 42
) -> tuple[np.ndarray, np.ndarray]:
    rng = np.random.default_rng(random_state)

    X = rng.uniform(0, 10, size=(n_samples, 1))
    noise = rng.normal(0, noise_std, size=n_samples)

    y = 3 * X[:, 0] + 5 + noise

    return X, y


def generate_changing_variance_data(
    n_samples: int = 1000,
    random_state: int = 42
) -> tuple[np.ndarray, np.ndarray]:
    rng = np.random.default_rng(random_state)

    X = rng.uniform(0, 10, size=(n_samples, 1))
    noise_std = 0.5 + 0.5 * X[:, 0]
    noise = rng.normal(0, noise_std, size=n_samples)

    y = 3 * X[:, 0] + 5 + noise

    return X, y


def generate_concept_drift_data(
    n_samples: int = 1000,
    change_point: int = 500,
    random_state: int = 42
) -> tuple[np.ndarray, np.ndarray]:
    rng = np.random.default_rng(random_state)

    X = rng.uniform(0, 10, size=(n_samples, 1))
    noise = rng.normal(0, 2.0, size=n_samples)

    y = np.empty(n_samples)

    y[:change_point] = 2 * X[:change_point, 0] + 5 + noise[:change_point]
    y[change_point:] = 5 * X[change_point:, 0] + 5 + noise[change_point:]

    return X, y
