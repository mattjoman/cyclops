# TODO

## General

- Implement a logging module
- Improve error handling (integrate with logging module?)
- Add testing (start with high-level system tests with pytest)

## Documentation

- Thoroughly document the workload plugin system
- Document the metric/group hierarchy and how they relate to metric backends
- Document metric backends & strategies for increasing accuracy and reducing
  noise

## CLI

- Add advanced options:
    - Pin to specific core (core 0 by default)
    - Include/exclude kernel for perf\_event\_open() metric groups

## Batch / Param-Sweep Orchestration

- Improve batch/param-sweep API boundaries
- Separate `batch` and `param_sweep` into separate files
- Move `batch` into `core/batch`
- Move batch aggregation code into `core/batch` (it belongs to batch)
- Add more aggregations (stddev etc.)

## Metric Groups

- Verify the effectiveness of the barriers and serialization in metric backends
- Move metric groups to their own files and register them like metric backends
- Add ARM-specific instruction metrics/groups
- Validate metric groups on registration (e.g. metrics have the same backend as
  their group)

## Workload

- Add a template workload plugin file for users to get users started
- Validate workloads on registration (e.g. workload params can be cast to `ull`
  and have a valid key and value)
- Add a cache coherence workload

## Experiments

- Do a brief explanation of the biased pattern length branch predictor
  experiment in the README
