import numpy as np


def aggregate_metrics(records: list[dict]) -> dict:
    metric_names = (
        "coverage",
        "average_width",
        "mae"
    )

    summary = {}

    for metric in metric_names:
        values = np.asarray(
            [record[metric] for record in records],
            dtype=float
        )

        summary[f"{metric}_mean"] = float(np.mean(values))
        summary[f"{metric}_std"] = float(np.std(values, ddof=1))

    return summary
