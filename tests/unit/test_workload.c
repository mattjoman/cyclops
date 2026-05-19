#include <assert.h>
#include <stddef.h>

#include "../include/workload.h"

int main()
{
    registry_t *reg = registry_get_reg_by_id(REG_ID_WORKLOAD);
    workload_t *wl;

    assert(reg != NULL);

    for (size_t i = 0; i < reg->n_registered; i++) {
        wl = (workload_t *)reg->registry[i];

        assert(wl != NULL);

        /* n_params and params must both be 0/NULL or both not 0/NULL */
        assert((wl->n_params == 0) == (wl->params == NULL));
    }

    return 0;
}
