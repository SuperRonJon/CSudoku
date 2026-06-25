#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sudoku.h"

#ifndef VERSION
#define VERSION "1.0"
#endif

#define BOARDTOTAL BOARDSIZE * BOARDSIZE

static const char *example_board = "x56xxx27872xx361xx8xxxxx46x5xxx47xxx4x9xxx7x5xxx65xxx4x35xxxxx7xx718xx32918xxx54x";

struct config
{
    bool borders;
    bool printbefore;
    char boardstr[BOARDTOTAL + 2];
};

void usage()
{
    puts("Usage:\n      sudoku [OPTIONS...] <board-string>");
}

void help()
{
    usage();
    puts("Options:");
    puts("  -p      Prints only the solved board and not the starting board");
    puts("  -b      Prints borders with board");
    puts("  -h      Prints the help menu");
    puts("  -v      Prints the version number");
}

void set_config(struct config *conf, int argc, char **argv)
{
    conf->borders = false;
    conf->printbefore = true;
    conf->boardstr[0] = '\0';

    int opt;
    while ((opt = getopt(argc, argv, "hvepb")) != -1)
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

bool solve_board(const struct config *conf)
{
    int board[BOARDTOTAL];
    
    int res;
    if ((res = init_board(board, conf->boardstr)) != SUCCESS)
    {
		fprintf(stderr, "Error creating board: %s\n", err2str(res));
        return false;
    }
    
    if (conf->printbefore)
	    print_board(board, conf->borders);

    const bool solved = solve(board);
    if (solved)
    {
        puts("Solved!");
        print_board(board, conf->borders);
    }
    else
    {
        puts("Unable to solve...");
    }
    return solved;
}

void solve_from_file(struct config *conf, FILE *f)
{
    bool skip = false;
    bool skip_next = false;
    const bool is_stdin = f == stdin;
    static const char *prompt = "Enter board string. \"exit\" to exit, \"help\" for help";
    if (is_stdin)
        puts(prompt);
    while (fgets(conf->boardstr, BOARDTOTAL + 2, f) != NULL)
    {
        if (strncmp(conf->boardstr, "exit", 4) == 0)
            return;
        if (strncmp(conf->boardstr, "help", 4) == 0)
        {
            help();
            continue;
        }
        if (strncmp(conf->boardstr, "example", 7) == 0)
        {
            fprintf(stdout, "%s\n", example_board);
            continue;
        }

        const size_t len = strlen(conf->boardstr);
        if (len == BOARDTOTAL + 1 && conf->boardstr[len - 1] != '\n')
            skip_next = true;
        else
            skip_next = false;

        if (!skip)
        {
            conf->boardstr[strcspn(conf->boardstr, "\n")] = '\0';
            solve_board(conf);
        }
        else
            skip = false;
        if (skip_next)
            skip = true;
    }
}

int main(int argc, char **argv)
{
    struct config conf;
    set_config(&conf, argc, argv);

    if (strlen(conf.boardstr) == 0)
    {
        solve_from_file(&conf, stdin);
        return 0;
    }
    size_t len;
    if ((len = strlen(conf.boardstr)) != 81)
    {
        fprintf(stderr, "Board string given must be 81 characters long, was %zu\n", len);
        exit(1);
    }

    solve_board(&conf);
	return 0;
}
