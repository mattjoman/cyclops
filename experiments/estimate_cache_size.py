import matplotlib.pyplot as plt
import pandas as pd

from cyclops import Cyclops, ParamSweep

BATCH_RUNS = 50
WARMUP_RUNS = 5

#AGGREGATE = "MIN"
#AGGREGATE = "MAX"
AGGREGATE = "MEDIAN"

WORKLOAD = "STRIDED_ARRAY_2"

L1D = 0
LLC = 1

def sweep_array_size_kib(cache: int):

    if cache == L1D:
        array_size_kib_low = 1
        array_size_kib_high = 100
        array_size_kib_step = 1
        metric_grp = "L1D_READS"
        metric = "L1D_READ_MISS_RATE"
    elif cache == LLC:
        array_size_kib_low = 500
        array_size_kib_high = 30000
        array_size_kib_step = 500
        metric_grp = "LLC_READS"
        metric = "LLC_READ_MISS_RATE"

    param_sweep = ParamSweep(
        key="array-size-kib",
        low=array_size_kib_low,
        high=array_size_kib_high,
        step=array_size_kib_step,
    )

    cyclops = Cyclops(
        workload=WORKLOAD,
        metric_grp=metric_grp,
        warmup_runs=WARMUP_RUNS,
        batch_runs=BATCH_RUNS,
        param_sweep=param_sweep,
    )
    cyclops.exec()

    df = pd.read_csv(
        f"param_sweep.csv",
        comment="#",
        index_col=param_sweep.key
    )

    return df.index.values, df[f"{metric}:{AGGREGATE}"].values

if __name__ == "__main__":

    x_L1D, y_L1D = sweep_array_size_kib(L1D)
    x_LLC, y_LLC = sweep_array_size_kib(LLC)

    plt.figure()
    plt.plot(x_L1D, y_L1D, marker="", label="L1D")
    plt.plot(x_LLC, y_LLC, marker="", label="LLC")
    plt.xscale("log")
    #plt.yscale("log")
    plt.xlabel("Array size (KiB)")
    plt.ylabel("Cache miss rate")
    plt.title("Cache Miss Rate vs Array Size")
    plt.grid(True)
    plt.ylim(0, 1)
    plt.legend()
    plt.savefig(f"estimate_cache_size.png")
    plt.close()
