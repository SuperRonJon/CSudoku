#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

const char *example_board = "x56xxx27872xx361xx8xxxxx46x5xxx47xxx4x9xxx7x5xxx65xxx4x35xxxxx7xx718xx32918xxx54x";

void usage()
{
    puts("Usage:\n      sudoku [OPTIONS...] <board-string>");
}

void help()
{
    usage();
    puts("Options:");
    puts("  --border,       -b      Prints borders with board");
    puts("  --count,        -c      Prints the number of possibility checks performed");
    puts("  --print-after,  -p      Prints only the solved board and not the starting board");
    puts("  --example,      -e      Prints an example input board string");
    puts("  --help,         -h      Prints the help menu");
    puts("  --version,      -v      Prints the version number");
}

void set_config(struct config *conf, int argc, char **argv)
{
    conf->borders = false;
    conf->printbefore = true;
    conf->count = false;
    conf->boardstr[0] = '\0';

    static struct option long_options[] = 
    {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"example", no_argument, NULL, 'e'},
        {"print-after", no_argument, NULL, 'p'},
        {"border", no_argument, NULL, 'b'},
        {"count", no_argument, NULL, 'c'},
        {0, 0, 0, 0},
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "hvepbc", long_options, NULL)) != -1)
    {
        switch (opt)
        {
            case 'h':
                help();
                exit(0);
            case 'v':
                puts("sudoku " VERSION);
                exit(0);
            case 'e':
                printf("Example board string: %s\n", example_board);
                exit(0);
            case 'p':
                conf->printbefore = false;
                break;
            case 'b':
                conf->borders = true;
                break;
            case 'c':
                conf->count = true;
                break;
            case '?':
                fprintf(stderr, "Invalid option %c given\n", optopt);
                exit(1);
        }
    }

    if (optind < argc)
    {
        strncpy(conf->boardstr, argv[optind], BOARDTOTAL + 1);
    }
}
