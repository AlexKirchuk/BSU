import csv
from pathlib import Path


def save_run_results(
    results: dict,
    output_path: str
) -> None:
    path = Path(output_path)
    path.parent.mkdir(parents=True, exist_ok=True)

    fieldnames = [
        "scenario",
        "method",
        "run",
        "coverage",
        "average_width",
        "mae"
    ]

    with path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=fieldnames)
        writer.writeheader()

        for scenario, methods in results.items():
            for method, records in methods.items():
                for record in records:
                    writer.writerow({
                        "scenario": scenario,
                        "method": method,
                        **record
                    })


def save_summary_results(
    summaries: dict,
    output_path: str
) -> None:
    path = Path(output_path)
    path.parent.mkdir(parents=True, exist_ok=True)

    fieldnames = [
        "scenario",
        "method",
        "coverage_mean",
        "coverage_std",
        "average_width_mean",
        "average_width_std",
        "mae_mean",
        "mae_std"
    ]

    with path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=fieldnames)
        writer.writeheader()

        for scenario, methods in summaries.items():
            for method, metrics in methods.items():
                writer.writerow({
                    "scenario": scenario,
                    "method": method,
                    **metrics
                })
