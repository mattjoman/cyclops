#include <stdlib.h>

#include "../include/workload.h"

#define STRIDE_BYTES 64 // one element per cache line

static unsigned long long array_elements;
static unsigned long long array_size_kib;

static int *array;
static unsigned long long *indices;

static void init_indices()
{
    indices = malloc(array_elements * sizeof(unsigned long long));
    for (unsigned long long i = 0; i < array_elements; i++) {
        indices[i] = i;
    }

    srand(42);
    for (unsigned long long i = array_elements - 1; i > 0; i--) {
        unsigned long long j = rand() % (i + 1);

        unsigned long long tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }
}

static void init(workload_t *wl)
{
    array_size_kib = wl_get_param_val(wl, "array-size-kib");
    array_elements = (array_size_kib << 10) / STRIDE_BYTES;

    init_indices();

    array = (int *)aligned_alloc(STRIDE_BYTES, STRIDE_BYTES * array_elements);
    for (unsigned long long i = 0; i < array_elements; i++) {
        array[i * (STRIDE_BYTES / sizeof(int))] = i;
    }
}

static void clean(void)
{
    free(array);
    free(indices);
}

__attribute__((noinline)) static void workload(void)
{
    volatile unsigned long long sum = 0;
    for (unsigned long long i = 0; i < array_elements; i++) {
        sum += array[indices[i] * (STRIDE_BYTES / sizeof(int))];
    }
}

static wl_param_t params[] = {
    {
        .key = "array-size-kib",
        .default_value = "1", // 1 element per cache line
    },
};

static workload_t wl = {
    .name = "STRIDED_ARRAY_2",

    .n_params = 1,
    .params = params,

    .init = init,
    .clean = clean,
    .workload = workload,
};

REGISTER_WORKLOAD(&wl)
