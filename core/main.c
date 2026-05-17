#include <stdio.h>

#include "../include/cli.h"
#include "../include/experiment.h"
#include "../include/workload.h"
#include "../include/metric_grp.h"

static const char help_text[] =
"Usage: ./cyclops [OPTIONS]\n"
"\n"
"Options:\n\n"
"  -h, --help                       Display this message\n"
"\n"
"  -w, --workload WORKLOAD          Select workload to benchmark\n"
"\n"
"  -m, --metric-group GROUP         Select a group of metrics to record\n"
"\n"
"  -r, --batch-runs RUNS            Number of runs in the batch\n"
"\n"
"  -u, --warmup-runs RUNS           Number of warmup runs\n"
"\n"
"  -p, --param KEY=VAL              Set a custom workload parameter for the\n"
"                                   batch(es)\n"
"\n"
"  -s, --param-sweep KEY=LOW:HIGH:STEP\n"
"                                   Sweep the selected workload parameter\n"
"                                   through a range of values (one batch\n"
"                                   will be run for each param value)\n"
"\n"
"  --batch-csv                      Write run-level data to csv files for\n"
"                                   each batch\n"
"\n"
"  --param-sweep-csv                Write aggregated batch data to\n"
"                                   'param_sweep.csv'\n"
"\n";

static void print_main_help_text()
{
    fputs(help_text, stdout);
}

int main(int argc, char *argv[])
{
    cyclops_cfg_t *cli_cfg = cli_cfg_init(argc, argv);
    if (!cli_cfg) {
        goto error;
    }

    if (!cli_cfg_validate(cli_cfg)) {
        goto error;
    }

    if (cli_cfg->display_help) {
        print_main_help_text();
        print_workload_guide();
        print_metric_grp_guide();
        goto success;
    }

    if (cli_cfg->ps_wl_param_key) {
        param_sweep_run(cli_cfg);
    } else {
        batch_single_run(cli_cfg);
    }

success:
    cli_cfg_destroy(cli_cfg);
    return 0;

error:
    cli_cfg_destroy(cli_cfg);
    return 1;
}
