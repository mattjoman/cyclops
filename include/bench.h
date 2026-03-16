#ifndef BENCH_H
#define BENCH_H

#include "./batch.h"
#include "./metric.h"

int bench_rdtscp(batch_conf_t batch_conf, batch_data_t *batch_data,
                                          void (*workload)(void));

int bench_perf_event(batch_conf_t batch_conf, batch_data_t *batch_data,
                                              void (*workload)(void));

#endif
