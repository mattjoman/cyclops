#include "../../../include/metric_grp.h"

static metric_id_t metrics[] = {
    METRIC_RDTSCP,
};

static metric_grp_t mg = {
    .name = "RDTSCP",
    .backend = METRIC_BE_ISA,
    .n_metrics = 1,
    .metrics = metrics,
};

REGISTER_MG(&mg)
