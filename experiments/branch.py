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

def run_experiment():

    param_sweep = ParamSweep(
        key="pattern-len",
        low=1,
        high=30000,
        step=100,
    )

    cyclops = Cyclops(
        workload=WORKLOAD,
        metric_grp=METRIC_GRP,
        warmup_runs=WARMUP_RUNS,
        batch_runs=BATCH_RUNS,
        params={
            "n-branches": 50000,
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

    x, y = run_experiment()

    plt.figure()
    plt.plot(x, y, marker="", label="")
    plt.xscale("log")
    #plt.yscale("log")
    plt.xlabel("Pattern Len")
    plt.ylabel(METRIC)
    plt.title(WORKLOAD)
    plt.grid(True)
    #plt.legend()
    plt.savefig(f"branch.png")
    plt.close()
