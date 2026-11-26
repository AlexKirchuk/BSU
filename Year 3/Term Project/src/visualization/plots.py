from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


SCENARIOS = (
    "stationary",
    "changing_variance",
    "concept_drift"
)

METHODS = (
    "sliding_window",
    "aci"
)


def _prepare_data(records: pd.DataFrame, scenario: str) -> pd.DataFrame:
    data = records[records["scenario"] == scenario].copy()

    if data.empty:
        raise ValueError(f"No records found for scenario: {scenario}")

    return data.sort_values(["method", "run", "time_step"])


def _plot_metric(
    data: pd.DataFrame,
    scenario: str,
    column: str,
    title: str,
    ylabel: str,
    filename: str,
    output_dir: Path,
    rolling_window: int | None = None,
    change_point: int | None = None
) -> None:
    plt.figure(figsize=(12, 6))

    for method in METHODS:
        method_data = data[data["method"] == method].copy()

        if rolling_window is not None:
            method_data[column] = (
                method_data.groupby("run")[column]
                .transform(
                    lambda values: values.rolling(
                        window=rolling_window,
                        min_periods=rolling_window
                    ).mean()
                )
            )

        summary = (
            method_data.groupby("time_step")[column]
            .agg(["mean", "std"])
            .reset_index()
        )

        summary["std"] = summary["std"].fillna(0)

        plt.plot(
            summary["time_step"],
            summary["mean"],
            label=method
        )

        plt.fill_between(
            summary["time_step"],
            summary["mean"] - summary["std"],
            summary["mean"] + summary["std"],
            alpha=0.15
        )

    plt.axhline(
        y=0.9 if column == "covered" else 0,
        linestyle="--",
        color="black",
        alpha=0.7,
        label="Target coverage (90%)" if column == "covered" else None
    )

    if change_point is not None:
        plt.axvline(
            x=change_point,
            linestyle=":",
            color="red",
            label="Concept drift"
        )

    plt.title(title)
    plt.xlabel("Time step")
    plt.ylabel(ylabel)
    plt.legend()
    plt.grid(alpha=0.3)
    plt.tight_layout()
    plt.savefig(output_dir / filename, dpi=300)
    plt.close()


def _plot_alpha_history(
    data: pd.DataFrame,
    scenario: str,
    output_dir: Path,
    change_point: int | None = None
) -> None:
    aci_data = data[data["method"] == "aci"].copy()

    if aci_data["alpha"].isna().all():
        return

    summary = (
        aci_data.groupby("time_step")["alpha"]
        .agg(["mean", "std"])
        .reset_index()
    )

    summary["std"] = summary["std"].fillna(0)

    plt.figure(figsize=(12, 6))

    plt.plot(
        summary["time_step"],
        summary["mean"],
        label="ACI alpha"
    )

    plt.fill_between(
        summary["time_step"],
        summary["mean"] - summary["std"],
        summary["mean"] + summary["std"],
        alpha=0.15
    )

    plt.axhline(
        y=0.1,
        linestyle="--",
        color="black",
        label="Target alpha (10%)"
    )

    if change_point is not None:
        plt.axvline(
            x=change_point,
            linestyle=":",
            color="red",
            label="Concept drift"
        )

    plt.title(f"ACI Alpha History — {scenario}")
    plt.xlabel("Time step")
    plt.ylabel("Alpha")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.tight_layout()
    plt.savefig(output_dir / f"{scenario}_alpha_history.png", dpi=300)
    plt.close()


def _plot_prediction_intervals(
    data: pd.DataFrame,
    scenario: str,
    output_dir: Path,
    change_point: int | None = None,
    run: int = 0
) -> None:
    fig, axes = plt.subplots(2, 1, figsize=(13, 10), sharex=True)

    for ax, method in zip(axes, METHODS):
        method_data = data[
            (data["method"] == method)
            & (data["run"] == run)
        ].sort_values("time_step")

        if method_data.empty:
            continue

        ax.plot(
            method_data["time_step"],
            method_data["y_true"],
            label="Actual values",
            color="black",
            alpha=0.65
        )

        ax.plot(
            method_data["time_step"],
            method_data["prediction"],
            label="Predictions",
            alpha=0.8
        )

        ax.fill_between(
            method_data["time_step"],
            method_data["lower_bound"],
            method_data["upper_bound"],
            alpha=0.2,
            label="Prediction interval"
        )

        if change_point is not None:
            ax.axvline(
                x=change_point,
                linestyle=":",
                color="red",
                label="Concept drift"
            )

        ax.set_title(method)
        ax.set_ylabel("Target value")
        ax.legend()
        ax.grid(alpha=0.3)

    axes[-1].set_xlabel("Time step")

    fig.suptitle(f"Prediction Intervals — {scenario}")
    fig.tight_layout()
    fig.savefig(output_dir / f"{scenario}_prediction_intervals.png", dpi=300)
    plt.close(fig)


def _plot_summary_metrics(
    summary_path: str,
    recovery_path: str,
    output_dir: Path
) -> None:
    summary = pd.read_csv(summary_path)

    metrics = [
        ("coverage", "Mean Coverage", "Coverage", 0.9),
        ("average_width", "Mean Interval Width", "Interval width", None),
        ("mae", "Mean Absolute Error", "MAE", None)
    ]

    scenarios = (
        "stationary",
        "changing_variance",
        "concept_drift"
    )

    methods = ("sliding_window", "aci")

    for column, title, ylabel, target in metrics:
        figure, ax = plt.subplots(figsize=(10, 6))

        x = np.arange(len(scenarios))
        width = 0.35

        for i, method in enumerate(methods):
            method_data = (
                summary[summary["method"] == method]
                .set_index("scenario")
                .reindex(scenarios)
            )

            means = method_data[f"{column}_mean"].to_numpy()
            stds = method_data[f"{column}_std"].to_numpy()

            ax.bar(
                x + (i - 0.5) * width,
                means,
                width,
                yerr=stds,
                capsize=4,
                label=method
            )

        if target is not None:
            ax.axhline(
                target,
                color="red",
                linestyle="--",
                label="Target coverage (90%)"
            )

        ax.set_title(title)
        ax.set_ylabel(ylabel)
        ax.set_xticks(x)
        ax.set_xticklabels(scenarios)
        ax.legend()
        ax.grid(axis="y", alpha=0.3)

        figure.tight_layout()
        figure.savefig(
            output_dir / f"summary_{column}.png",
            dpi=300
        )
        plt.close(figure)

    recovery = pd.read_csv(recovery_path)

    recovery_summary = (
        recovery.groupby("method")
        .agg(
            total_runs=("method", "size"),
            successful_runs=("recovery_time", "count"),
            mean_recovery_time=("recovery_time", "mean"),
            std_recovery_time=("recovery_time", "std")
        )
        .reindex(METHODS)
    )

    recovery_summary["recovery_rate"] = (
            recovery_summary["successful_runs"]
            / recovery_summary["total_runs"]
    ).fillna(0)

    figure, axes = plt.subplots(1, 2, figsize=(13, 5))

    methods = list(METHODS)

    mean_times = recovery_summary["mean_recovery_time"].to_numpy()
    std_times = (
        recovery_summary["std_recovery_time"]
        .fillna(0)
        .to_numpy()
    )

    recovery_rates = recovery_summary["recovery_rate"].to_numpy()

    axes[0].bar(
        methods,
        mean_times,
        yerr=std_times,
        capsize=5
    )

    axes[0].set_title("Mean Recovery Time")
    axes[0].set_ylabel("Recovery time (time steps)")
    axes[0].grid(axis="y", alpha=0.3)

    axes[1].bar(
        methods,
        recovery_rates
    )

    axes[1].set_title("Recovery Rate")
    axes[1].set_ylabel("Successful recoveries")
    axes[1].set_ylim(0, 1.05)
    axes[1].yaxis.set_major_formatter(
        plt.FuncFormatter(lambda value, _: f"{value:.0%}")
    )
    axes[1].grid(axis="y", alpha=0.3)

    for index, rate in enumerate(recovery_rates):
        axes[1].text(
            index,
            rate + 0.02,
            f"{rate:.1%}",
            ha="center"
        )

    figure.suptitle("Recovery Analysis after Concept Drift")
    figure.tight_layout()
    figure.savefig(
        output_dir / "summary_recovery_time.png",
        dpi=300
    )
    plt.close(figure)


def plot_all_results(
    csv_path: str = "results/temporal.csv",
    output_dir: str = "results/plots",
    rolling_window: int = 50,
    change_point: int = 500
) -> None:
    records = pd.read_csv(csv_path)

    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)

    for scenario in SCENARIOS:
        data = _prepare_data(records, scenario)

        drift = change_point if scenario == "concept_drift" else None

        _plot_metric(
            data=data,
            scenario=scenario,
            column="covered",
            title=f"Temporal Coverage — {scenario}",
            ylabel="Coverage",
            filename=f"{scenario}_coverage.png",
            output_dir=output_path,
            change_point=drift
        )

        _plot_metric(
            data=data,
            scenario=scenario,
            column="covered",
            title=f"Rolling Coverage — {scenario}",
            ylabel="Coverage",
            filename=f"{scenario}_rolling_coverage.png",
            output_dir=output_path,
            rolling_window=rolling_window,
            change_point=drift
        )

        data["interval_width"] = (
            data["upper_bound"] - data["lower_bound"]
        )

        _plot_metric(
            data=data,
            scenario=scenario,
            column="interval_width",
            title=f"Temporal Interval Width — {scenario}",
            ylabel="Interval width",
            filename=f"{scenario}_interval_width.png",
            output_dir=output_path,
            change_point=drift
        )

        _plot_metric(
            data=data,
            scenario=scenario,
            column="interval_width",
            title=f"Rolling Interval Width — {scenario}",
            ylabel="Interval width",
            filename=f"{scenario}_rolling_interval_width.png",
            output_dir=output_path,
            rolling_window=rolling_window,
            change_point=drift
        )

        _plot_alpha_history(
            data=data,
            scenario=scenario,
            output_dir=output_path,
            change_point=drift
        )

        _plot_prediction_intervals(
            data=data,
            scenario=scenario,
            output_dir=output_path,
            change_point=drift,
            run=0
        )

    _plot_summary_metrics(
        summary_path=str(Path(csv_path).parent / "summary.csv"),
        recovery_path=str(Path(csv_path).parent / "recovery.csv"),
        output_dir=output_path
    )

    print(f"Plots saved to: {output_path.resolve()}")
