#ifndef METRIC_BACKEND_H
#define METRIC_BACKEND_H

#include "../../include/metric_grp.h"

typedef struct {
    size_t n_registered;
    metric_backend_t **registry;
} metric_backend_registry_t;

metric_backend_registry_t *metric_be_registry_get_registry(void);

void metric_be_register(metric_backend_t *backend);

#define REGISTER_BACKEND(be_ptr) \
    static void __attribute((constructor)) register_be(void) { \
        metric_be_register(be_ptr); \
    }

#endif
