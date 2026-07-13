#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

#include "sudoku.h"

#ifndef VERSION
#define VERSION "1.1"
#endif

#define BOARDTOTAL BOARDSIZE * BOARDSIZE

extern const char *example_board;

struct config
{
    bool borders;
    bool printbefore;
    bool count;
    char boardstr[BOARDTOTAL + 2];
};

void usage();
void help();
void set_config(struct config *conf, int argc, char **argv);
#endif
