#include <stdlib.h>

#include "../include/workload.h"

static int stride_bytes;
static int array_elements;

static int *array;

static void init(wl_arg_slice_t *wl_args)
{
    stride_bytes = get_wl_param_val(WL_STRIDED_ARRAY, wl_args, "stride-bytes");
    array_elements = get_wl_param_val(WL_STRIDED_ARRAY, wl_args,
                                                            "array-elements");
    array = (int *)aligned_alloc(stride_bytes, stride_bytes * array_elements);
    for (int i = 0; i < array_elements; i++) {
        array[i * (stride_bytes / sizeof(int))] = i;
    }
}

static void clean(void)
{
    free(array);
}

__attribute__((noinline))
static void workload(void)
{
    volatile int sum = 0;
    for (int i = 0; i < array_elements; i++) {
        sum += array[i * (stride_bytes / sizeof(int))];
    }
}

static const wl_param_t params[] = {
    {
        .key = "stride-bytes",
        .default_value = "64", // 1 element per cache line
    },
    {
        .key = "array-elements",
        .default_value = "1000000",
    },
};

workload_t wl_strided_array = {
    .id = WL_STRIDED_ARRAY,
    .name = "STRIDED_ARRAY",

    .n_params = 2,
    .params = params,

    .init = init,
    .clean = clean,
    .workload = workload,
};
