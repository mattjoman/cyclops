#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../include/metric_grp.h"

int mg_n_metrics_by_type(metric_grp_t *mg, metric_type_t type)
{
    int counter = 0;
    for (int i = 0; i < mg->n_metrics; i++) {
        const metric_t *m = metric_get_by_id(mg->metrics[i]);
        if (m->type == type) {
            counter++;
        }
    }
    return counter;
}

const metric_t *mg_get_nth_metric_by_type(metric_grp_t *mg,
                                          int n,
                                          metric_type_t type)
{
    int counter = 0;
    for (int i = 0; i < mg->n_metrics; i++) {

        const metric_t *m = metric_get_by_id(mg->metrics[i]);

        if (m->type == type) {
            if (counter == n) {
                return m;
            } else {
                counter++;
            }
        }
    }
    fprintf(stderr, "Couldn't find nth metric id\n");
    exit(1);
    return NULL;
}

metric_grp_t *mg_get_by_name(const char *name)
{
    registry_t *reg = registry_get_reg_by_id(REG_ID_METRIC_GRP);
    metric_grp_t *mg;

    if (name == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < reg->n_registered; i++) {
        mg = (metric_grp_t *)reg->registry[i];
        if (strcmp(name, mg->name) == 0) {
            return mg;
        }
    }

    fprintf(stderr, "No metric group with name '%s'\n", name);
    return NULL;
}

void print_metric_grp_guide(void)
{
    registry_t *reg = registry_get_reg_by_id(REG_ID_METRIC_GRP);
    metric_grp_t *mg;

    printf("Metric groups:\n\n");

    for (size_t i = 0; i < reg->n_registered; i++) {
        mg = (metric_grp_t *)reg->registry[i];
        printf("  %s\n", mg->name);
    }
}
