#ifndef SUDOKU_H
#define SUDOKU_H

#include <stddef.h>
#include <stdbool.h>

#define INVALID_LENGTH -1
#define INVALID_CHARACTER -2
#define SUCCESS 0

#ifndef BOARDSIZE
#define BOARDSIZE 9
#endif

int init_board(int *board, const char *const board_string);
void print_board(int *board, const bool borders);
bool solve(int *board, unsigned long long *counter);
bool is_possibility(int *board, const int number, const size_t row, const size_t col);
char *err2str(const int errcode);

static inline int *board_value(int *board, const size_t row, const size_t col)
{
    const size_t i = (BOARDSIZE * row) + col;
    return &board[i];
}
    

#endif
