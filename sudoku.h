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
int *board_value(int *board, const size_t row, const size_t col);
bool solve(int *board);
bool is_possibility(int *board, const int number, const size_t row, const size_t col);
char *err2str(const int errcode);

#endif
