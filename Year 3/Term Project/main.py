from src.data.generator import (
    generate_stationary_data,
    generate_changing_variance_data,
    generate_concept_drift_data
)
from src.experiments.runner import run_multiple_experiments
from src.experiments.export import (
    save_run_results,
    save_summary_results
)
from src.experiments.temporal_export import (
    save_temporal_results,
    save_recovery_results
)
from src.metrics.recovery import aggregate_recovery_times
from src.visualization.plots import plot_all_results


def main() -> None:
    scenarios = [
        ("stationary", generate_stationary_data, None),
        ("changing_variance", generate_changing_variance_data, None),
        ("concept_drift", generate_concept_drift_data, 500)
    ]

    all_runs = {}
    all_summaries = {}
    all_temporal_records = []
    all_recovery_records = []

    for scenario_name, generator, change_point in scenarios:
        print(f"\nRunning scenario: {scenario_name}")

        experiment_results = run_multiple_experiments(
            generator=generator,
            scenario_name=scenario_name,
            n_runs=30,
            alpha=0.1,
            gamma=0.01,
            window_size=100,
            warmup_size=100,
            change_point=change_point
        )

        all_runs[scenario_name] = experiment_results["runs"]
        all_summaries[scenario_name] = experiment_results["summaries"]

        all_temporal_records.extend(
            experiment_results["temporal_records"]
        )

        all_recovery_records.extend(
            experiment_results["recovery_records"]
        )

        for method, metrics in experiment_results["summaries"].items():
            print(f"\nMethod: {method}")

            for metric, value in metrics.items():
                print(f"{metric}: {value:.4f}")

    save_run_results(all_runs, "results/runs.csv")
    save_summary_results(all_summaries, "results/summary.csv")

    save_temporal_results(
        all_temporal_records,
        "results/temporal.csv"
    )

    save_recovery_results(
        all_recovery_records,
        "results/recovery.csv"
    )

    for scenario_name, _, _ in scenarios:
        plot_all_results(
            csv_path="results/temporal.csv",
            output_dir="results/plots",
            rolling_window=50,
            change_point=500
        )

    if all_recovery_records:
        print("\nRecovery analysis")

        for method in ("sliding_window", "aci"):
            records = [
                record
                for record in all_recovery_records
                if record["method"] == method
            ]

            summary = aggregate_recovery_times(records)

            print(f"\nMethod: {method}")

            for metric, value in summary.items():
                print(f"{metric}: {value}")

    print("\nAll experiments completed.")
    print("Results saved to the results directory.")


if __name__ == "__main__":
    main()
