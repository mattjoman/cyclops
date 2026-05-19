#include <assert.h>
#include <stddef.h>

#include "../include/workload.h"

void test1()
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
}

void test2()
{
    workload_t *wl;

    wl = wl_get_by_name("NOT_A_REAL_WORKLOAD");
    assert(wl == NULL);

    wl = wl_get_by_name(NULL);
    assert(wl == NULL);

    wl = wl_get_by_name("STRIDED_ARRAY");
    assert(wl != NULL);
}

int main()
{
    test1();
    test2();

    return 0;
}
