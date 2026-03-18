#ifndef WORKLOAD_H
#define WORKLOAD_H

enum {
    WL_CONTIGUOUS_ARRAY,
    WL_SCATTERED_ARRAY,
    WL_STRIDED_ARRAY,
    N_WORKLOADS,
};

#define MAX_WL_PARAMS 5

typedef struct {
    const char *key;
    const char *value;
} wl_arg_t;

typedef struct {
    int n_args;
    wl_arg_t args[MAX_WL_PARAMS];
} wl_arg_slice_t;

typedef struct {
    const char *key;
    const char *default_value;
} wl_param_t;

typedef struct workload {
    int id;
    const char* name;

    const int n_params;
    const wl_param_t *params;

    void (*init)(wl_arg_slice_t *wl_args);
    void (*clean)(void);
    void (*workload)(void);
} workload_t;

extern workload_t *all_workloads[N_WORKLOADS];

extern workload_t wl_contiguous_array;
extern workload_t wl_scattered_array;
extern workload_t wl_strided_array;

int get_wl_param_val(int wl_id, wl_arg_slice_t *wl_args, const char *key);

#endif
