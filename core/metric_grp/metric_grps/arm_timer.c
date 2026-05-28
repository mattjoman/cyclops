#include "../../../include/metric_grp.h"

static metric_id_t metrics[] = {
    METRIC_ARM,
};

static metric_grp_t mg = {
    .name = "ARM_TIMER",
    .backend = METRIC_BE_ISA,
    .n_metrics = 1,
    .metrics = metrics,
};

REGISTER_MG(&mg)
