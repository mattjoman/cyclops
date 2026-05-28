#include <assert.h>
#include <stddef.h>

#include "../include/registry.h"

int main()
{
    registry_t *reg = registry_get_reg_by_id(REG_ID_WORKLOAD);
    assert(reg != NULL);
    assert(reg->id == REG_ID_WORKLOAD);
    assert(reg->n_registered > 0);

    reg = registry_get_reg_by_id(REG_ID_METRIC_GRP);
    assert(reg != NULL);
    assert(reg->id == REG_ID_METRIC_GRP);
    assert(reg->n_registered > 0);

    reg = registry_get_reg_by_id(REG_ID_METRIC_BACKEND);
    assert(reg != NULL);
    assert(reg->id == REG_ID_METRIC_BACKEND);
    assert(reg->n_registered > 0);

    return 0;
}
