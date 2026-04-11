#ifndef BENCH_H
#define BENCH_H

#include "./batch.h"
#include "./metric.h"

typedef void (*bench_func_t)(
    batch_conf_t *,
    batch_data_t *,
    void (*)(void)
);

bench_func_t get_timer_bench_func(const metric_grp_t *mg);


int bench_perf_event_open(batch_conf_t *batch_cfg,
                          batch_data_t *batch_data,
                          void (*workload)(void));

#endif
