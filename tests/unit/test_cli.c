#include <stddef.h>
#include <assert.h>
#include <getopt.h>

#include "../../include/cli.h"
#include "../../include/cyclops.h"

void test_1()
{
    optind = 0;

    int argc = 2;
    char *argv[] = {
        "./cyclops",
        "-h",
        NULL
    };

    cyclops_cfg_t *cli_cfg = cli_cfg_init(argc, argv);
    bool is_valid = cli_cfg_validate(cli_cfg);

    assert(is_valid);
    assert(cli_cfg->display_help);

    cli_cfg_destroy(cli_cfg);
}

void test_2()
{
    optind = 0;

    int argc = 5;
    char *argv[] = {
        "./cyclops",
        "-w", "BRANCH",
        "-m", "IPC",
        NULL
    };

    cyclops_cfg_t *cli_cfg = cli_cfg_init(argc, argv);
    bool is_valid = cli_cfg_validate(cli_cfg);

    assert(is_valid);

    cli_cfg_destroy(cli_cfg);
}

void test_3()
{
    optind = 0;

    int argc = 4;
    char *argv[] = {
        "./cyclops",
        "-w", "BRANCH",
        "-m",
        NULL
    };

    cyclops_cfg_t *cli_cfg = cli_cfg_init(argc, argv);
    bool is_valid = cli_cfg_validate(cli_cfg);

    assert(!is_valid);

    cli_cfg_destroy(cli_cfg);
}

int main()
{
    test_1();
    test_2();
}
