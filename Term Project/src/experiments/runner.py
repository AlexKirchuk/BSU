from collections.abc import Callable

from src.experiments.online_experiment import run_online_experiment
from src.experiments.temporal_export import build_temporal_records
from src.metrics.aggregation import aggregate_metrics
from src.metrics.evaluation import calculate_metrics
from src.metrics.temporal import (
    calculate_rolling_coverage,
    calculate_recovery_time
)


def run_multiple_experiments(
    generator: Callable,
    scenario_name: str,
    n_runs: int = 30,
    alpha: float = 0.1,
    gamma: float = 0.01,
    window_size: int = 100,
    warmup_size: int = 100,
    change_point: int | None = None
) -> dict:
    methods = ("sliding_window", "aci")

    all_results = {
        method: []
        for method in methods
    }

    temporal_records = []
    recovery_records = []

    for run in range(n_runs):
        X, y = generator(random_state=run)

        for method in methods:
            results = run_online_experiment(
                X=X,
                y=y,
                method=method,
                alpha=alpha,
                gamma=gamma,
                window_size=window_size,
                warmup_size=warmup_size
            )

            start = results["evaluation_start"]

            y_true = results["actual_values"][start:]
            predictions = results["predictions"][start:]
            lower = results["lower_bounds"][start:]
            upper = results["upper_bounds"][start:]
            indices = results["indices"][start:]

            metrics = calculate_metrics(
                y_true=y_true,
                predictions=predictions,
                lower_bounds=lower,
                upper_bounds=upper
            )

            all_results[method].append({
                "run": run,
                **metrics
            })

            temporal_records.extend(
                build_temporal_records(
                    scenario=scenario_name,
                    method=method,
                    run=run,
                    results=results,
                    evaluation_start=start
                )
            )

            if change_point is not None:
                rolling_coverage = calculate_rolling_coverage(
                    y_true=y_true,
                    lower_bounds=lower,
                    upper_bounds=upper,
                    window_size=20
                )

                recovery_time = calculate_recovery_time(
                    rolling_coverage=rolling_coverage,
                    indices=indices,
                    change_point=change_point
                )

                recovery_records.append({
                    "scenario": scenario_name,
                    "method": method,
                    "run": run,
                    "recovery_time": recovery_time
                })

    summaries = {
        method: aggregate_metrics(records)
        for method, records in all_results.items()
    }

    return {
        "runs": all_results,
        "summaries": summaries,
        "temporal_records": temporal_records,
        "recovery_records": recovery_records
    }
