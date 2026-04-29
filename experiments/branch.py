import matplotlib.pyplot as plt
import pandas as pd

from cyclops import Cyclops, ParamSweep

BATCH_RUNS = 1
WARMUP_RUNS = 0

#AGGREGATE = "MIN"
#AGGREGATE = "MAX"
AGGREGATE = "MEDIAN"

WORKLOAD = "BRANCH"

METRIC_GRP = "BRANCH"
METRIC = "BRANCH_MISPRED_RATE"
#METRIC_GRP = "BPU_READS"
#METRIC = "BPU_READ_MISS_RATE"

def run_experiment(bias: int):

    param_sweep = ParamSweep(
        key="pattern-len",
        low=1,
        high=100000,
        step=100,
    )

    cyclops = Cyclops(
        workload=WORKLOAD,
        metric_grp=METRIC_GRP,
        warmup_runs=WARMUP_RUNS,
        batch_runs=BATCH_RUNS,
        params={
            "n-branches": 100000,
            "bias": bias,
        },
        param_sweep=param_sweep,
    )
    cyclops.exec()

    df = pd.read_csv(
        f"{METRIC}.csv",
        comment="#",
        index_col=param_sweep.key
    )

    return df.index.values, df[AGGREGATE].values

if __name__ == "__main__":

    #biases = [50, 60, 70, 80, 90, 95, 99]
    biases = [50, 40, 30, 20, 10, 5, 1]

    data = []
    for bias in biases:
        x, y = run_experiment(bias)
        data.append({ "x": x, "y": y, "bias": bias})

    plt.figure()

    for d in data:
        plt.plot(d["x"], d["y"], marker="", label=f"Bias: {d["bias"]}")

    #plt.xscale("log")
    #plt.yscale("log")
    plt.xlabel("Pattern Len")
    plt.ylabel(METRIC)
    plt.title(WORKLOAD)
    plt.grid(True)
    plt.legend()
    plt.savefig(f"branch.png")
    plt.close()
