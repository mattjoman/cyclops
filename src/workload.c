#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/workload.h"

workload_t *all_workloads[N_WORKLOADS] = {
    [WL_CONTIGUOUS_ARRAY] = &wl_contiguous_array,
    [WL_SCATTERED_ARRAY] = &wl_scattered_array,
    [WL_STRIDED_ARRAY] = &wl_strided_array,
};

/*
 * Returns the workload parameter value given a parameter key.
 *
 * If no arg is provided for this param by the user (with --param key=value),
 * use the param's default value.
 */
int get_wl_param_val(int wl_id, wl_arg_slice_t *wl_args, const char *key)
{
    const int n_params = all_workloads[wl_id]->n_params;
    const wl_param_t *params = all_workloads[wl_id]->params;

    for (int i = 0; i < wl_args->n_args; i++) {
        if (strcmp(key, wl_args->args[i].key) == 0) {
            return atoi(wl_args->args[i].value);
        }
    }

    for (int i = 0; i < n_params; i++) {
        if (strcmp(key, params[i].key) == 0) {
            return atoi(params[i].default_value);
        };
    }

    fprintf(stderr, "Invalid workload param key '%s'\n", key);
    exit(1);
    return 0;
}
