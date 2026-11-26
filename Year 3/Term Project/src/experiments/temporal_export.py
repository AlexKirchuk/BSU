import csv
from pathlib import Path

import numpy as np


def save_temporal_results(
    records: list[dict],
    output_path: str
) -> None:
    path = Path(output_path)
    path.parent.mkdir(parents=True, exist_ok=True)

    fieldnames = [
        "scenario",
        "method",
        "run",
        "time_step",
        "y_true",
        "prediction",
        "lower_bound",
        "upper_bound",
        "covered",
        "interval_width",
        "alpha"
    ]

    with path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(records)


def build_temporal_records(
    scenario: str,
    method: str,
    run: int,
    results: dict,
    evaluation_start: int
) -> list[dict]:
    records = []

    for i in range(evaluation_start, len(results["indices"])):
        y_true = float(results["actual_values"][i])
        prediction = float(results["predictions"][i])
        lower = float(results["lower_bounds"][i])
        upper = float(results["upper_bounds"][i])

        alpha = None

        if method == "aci":
            alpha = float(results["alpha_history"][i])

        records.append({
            "scenario": scenario,
            "method": method,
            "run": run,
            "time_step": int(results["indices"][i]),
            "y_true": y_true,
            "prediction": prediction,
            "lower_bound": lower,
            "upper_bound": upper,
            "covered": int(lower <= y_true <= upper),
            "interval_width": upper - lower,
            "alpha": alpha
        })

    return records


def save_recovery_results(
    records: list[dict],
    output_path: str
) -> None:
    path = Path(output_path)
    path.parent.mkdir(parents=True, exist_ok=True)

    fieldnames = [
        "scenario",
        "method",
        "run",
        "recovery_time"
    ]

    with path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(records)
