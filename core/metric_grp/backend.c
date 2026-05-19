#include <stdlib.h>
#include <stddef.h>

#include "../../include/metric_grp.h"
#include "./backend.h"

metric_backend_t *metric_backend_get(metric_backend_id_t id)
{
    registry_t *reg = registry_get_reg_by_id(REG_ID_METRIC_BACKEND);
    metric_backend_t *metric_be;

    for (size_t i = 0; i < reg->n_registered; i++) {
        metric_be = (metric_backend_t *)reg->registry[i];

        if (metric_be->id == id) {
            return metric_be;
        }
    }

    return NULL;
}
