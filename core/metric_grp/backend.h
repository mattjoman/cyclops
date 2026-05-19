#ifndef METRIC_BACKEND_H
#define METRIC_BACKEND_H

#include "../../include/metric_grp.h"

#define REGISTER_BACKEND(be_ptr) \
    static void __attribute((constructor)) _registry_register_object(void) { \
        registry_register_object((void *)be_ptr, REG_ID_METRIC_BACKEND); \
    }

metric_backend_t *metric_backend_get(metric_backend_id_t id);

#endif
