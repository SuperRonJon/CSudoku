#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sudoku.h"
#include "config.h"

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

    unsigned long long counter = 0;
    unsigned long long *count_ptr = conf->count ? &counter : NULL;
    const bool solved = solve(board, count_ptr);
    if (solved)
    {
        if (conf->count)
            printf("Solved in %llu checks!\n", counter);
        else
            puts("Solved!");
        print_board(board, conf->borders);
    }
    else
    {
        if (conf->count)
            printf("Unable to solve in %llu checks...\n", counter);
        else
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
