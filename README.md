# Cyclops README

**Cyclops** is a highly scriptable and extensible framework for
reverse-engineering CPU architecture.

## Build and Run

```bash
# clone repository
git clone https://mj-penney/cyclops.git cyclops

# enter repository
cd cyclops

# build
make

# run (generate help text)
./cyclops -h
```

## What Makes Cyclops Powerful

### Workloads

- Choose from a range of built-in workloads to put targeted pressure on the CPU
- Create custom workloads using the workload plugin system
- Configure workloads at runtime from the command line with workload params

### Metric Groups

- Record groups of metrics while the workload runs (e.g. PMU data via the Linux
  perf subsystem, and ISA-specific metrics like `rdtscp`)
- Sensible setup by default to improve accuracy and reproducibility (e.g.
  pinning the thread and excluding the kernel from PMU data)
- Metric groups can include derived metrics like instructions per cycles (IPC)

### Run Experiments with One Command

- Run a single batch, setting number of warmup runs, recorded batch runs, and
  any workload params
- Run many batches, sweeping through a range of workload param values while
  keeping the others constant, with a single command
    - This makes it quick and easy to explore parameter spaces

### Visualise Experiments with CSV Output

- Param sweeps will create a CSV file with various aggregate values, for each
  metric, for each batch
    - This makes it easy to create plots of recorded data vs param-values
- Optionally, unaggregated run-level data for each metric and batch can also
  be written to CSV files

## Example Usage

### Example 1

- Single batch
- 10 warmup runs
- 20 batch runs
- `BRANCH` workload with default params
- `IPC` metric group

```bash
./cyclops -u 10 -r 20 -w BRANCH -m IPC
```

### Example 2

- 3 warmup runs
- 5 batch runs
- `STRIDED_ARRAY` workload
- `L1D_READS` metric group
- 19 batches, sweeping the `array-elements` param from 10 to 100 in steps of 5

```bash
./cyclops -u 3 -r 5 -w STRIDED_ARRAY -m L1D_READS -s array-elements=10:100:5
```

## Experiments

In `experiments/` there are example Python scripts for running experiments.
To run these experiments, you will first need to build the `cyclops` binary
(see above).

You will then need to create a Python virtual environment and install the
necessary packages:

```bash
cd experiments
python -m venv venv
pip install -r requirements.txt
```

Before running the example experiments, activate the virtual environment you
just created:

```bash
source venv/bin/activate
```

Then run the experiments:

```bash
python3 estimate_cache_size.py
python3 branch.py
```

Figures (png) will be saved in `experiments/`.

See [my website](https://matthewpenney.net) for investigations and writeups
using **Cyclops**.
