#include <stdlib.h>
#include <stddef.h>

#include "../../include/metric_grp.h"
#include "./backend.h"

static metric_backend_registry_t metric_be_registry = {
    .n_registered = 0,
    .registry = NULL,
};

void metric_be_register(metric_backend_t *be)
{
    metric_be_registry.registry = realloc(metric_be_registry.registry,
                                          (metric_be_registry.n_registered + 1)
                                          * sizeof(metric_backend_t *));
    metric_be_registry.registry[metric_be_registry.n_registered++] = be;
}

metric_backend_registry_t *metric_be_registry_get_registry(void)
{
    return &metric_be_registry;
}

metric_backend_t *metric_backend_get(metric_backend_id_t id)
{
    for (size_t i = 0; i < metric_be_registry.n_registered; i++) {
        metric_backend_t *metric_be = metric_be_registry.registry[i];

        if (metric_be->id == id) {
            return metric_be;
        }
    }
    return NULL;
}
