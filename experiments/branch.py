import matplotlib.pyplot as plt
import pandas as pd

from cyclops import Cyclops, ParamSweep

BATCH_RUNS = 3
WARMUP_RUNS = 1

#AGGREGATE = "MIN"
#AGGREGATE = "MAX"
AGGREGATE = "MEDIAN"

WORKLOAD = "BRANCH"

METRIC_GRP = "BRANCH"
METRIC = "BRANCH_MISPREDICTIONS"
#METRIC_GRP = "BPU_READS"
#METRIC = "BPU_READ_MISS_RATE"

N_BRANCHES = 100000

def sweep_pattern_len(bias: int):

    param_sweep = ParamSweep(
        key="pattern-len",
        low=100,
        high=100000,
        step=100,
    )

    cyclops = Cyclops(
        workload=WORKLOAD,
        metric_grp=METRIC_GRP,
        warmup_runs=WARMUP_RUNS,
        batch_runs=BATCH_RUNS,
        params={
            "n-branches": N_BRANCHES,
            "bias": bias,
        },
        param_sweep=param_sweep,
        #csv_all=True,
    )
    cyclops.exec()

    df = pd.read_csv(
        f"param_sweep.csv",
        comment="#",
        index_col=param_sweep.key
    )

    return df.index.values, (df[f"{METRIC}:{AGGREGATE}"].values / N_BRANCHES)

def run_bias_experiment(bias_take: bool):

    if bias_take:
        biases = [50, 60, 70, 80, 90, 95, 99]
        file_name = "branch_bias_take.png"
        figure_title = "Misprediction Rate (bias: take branch)"
    else:
        biases = [50, 40, 30, 20, 10, 5, 1]
        file_name = "branch_bias_dont_take.png"
        figure_title = "Misprediction Rate (bias: don't take branch)"

    data = []
    for bias in biases:
        x, y = sweep_pattern_len(bias)
        data.append({ "x": x, "y": y, "bias": bias})

    plt.figure()

    for d in data:
        plt.plot(d["x"], d["y"], marker="", label=f"Bias: {d["bias"]}")

    #plt.xscale("log")
    #plt.yscale("log")
    plt.xlabel("Pattern Lenth")
    plt.ylabel(METRIC)
    plt.title(figure_title)
    plt.grid(True)
    plt.ylim(0, 1)
    plt.legend(loc='center right', bbox_to_anchor=(1, 0.5))
    plt.savefig(file_name)
    plt.close()

if __name__ == "__main__":
    run_bias_experiment(True)
    run_bias_experiment(False)
