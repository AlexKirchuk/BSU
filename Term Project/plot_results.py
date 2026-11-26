from pathlib import Path

from src.visualization.plots import plot_all_results


def main() -> None:
    project_dir = Path(__file__).resolve().parent

    csv_path = project_dir / "results" / "temporal.csv"
    output_dir = project_dir / "results" / "plots"

    if not csv_path.exists():
        raise FileNotFoundError(
            f"Experiment results not found: {csv_path}. "
            "Run main.py first."
        )

    plot_all_results(
        csv_path=str(csv_path),
        output_dir=str(output_dir),
        rolling_window=50,
        change_point=500
    )


if __name__ == "__main__":
    main()
