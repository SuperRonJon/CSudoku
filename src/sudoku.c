#include <stdio.h>
#include <string.h>

#include "sudoku.h"

static inline bool is_empty_char(const char c)
{
    return (c == 'x' || c == 'X' || c == '.' || c == '0' || c == 'O' || c == 'o');
}

static inline bool row_contains(int *board, const int number, const size_t row)
{
    for (size_t i = 0; i < BOARDSIZE; i++)
    {
        if (*board_value(board, row, i) == number)
            return true;
    }
    return false;
}

static inline bool column_contains(int *board, const int number, const size_t col)
{
    for (size_t i = 0; i < BOARDSIZE; i++)
    {
        if (*board_value(board, i, col) == number)
            return true;
    }
    return false;
}

static inline bool square_contains(int *board, const int number, const size_t row, const size_t col)
{
    const size_t start_row = row - (row % 3);
    const size_t start_col = col - (col % 3);

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (*board_value(board, i + start_row, j + start_col) == number)
                return true;
        }
    }
    return false;
}

int init_board(int *board, const char *const board_string)
{
    const size_t board_len = BOARDSIZE * BOARDSIZE;
    if (strlen(board_string) != board_len)
        return INVALID_LENGTH;
    for (size_t i = 0; i < board_len; i++)
    {
        if (is_empty_char(board_string[i]))
            board[i] = -1;
        else if(board_string[i] >= '0' && board_string[i] <= '9')
            board[i] = board_string[i] - '0';
        else
            return INVALID_CHARACTER;
    }
    return SUCCESS;
}

bool is_possibility(int *board, const int number, const size_t row, const size_t col)
{
    return (!row_contains(board, number, row) && !column_contains(board, number, col) && !square_contains(board, number, row, col));
}

static bool _solve(int *board, size_t row, size_t col, unsigned long long *counter)
{
    if (row == BOARDSIZE - 1 && col == BOARDSIZE)
        return true;
    if (col == BOARDSIZE)
    {
        row++;
        col = 0;
    }

    if (*board_value(board, row, col) != -1)
        return _solve(board, row, col + 1, counter);

    for (int i = 1; i <= BOARDSIZE; i++)
    {
        if (counter != NULL)
            (*counter)++;
        if (is_possibility(board, i, row, col))
        {
            *board_value(board, row, col) = i;
            if (_solve(board, row, col + 1, counter))
                return true;
            *board_value(board, row, col) = -1;
        }
    }
    return false;
}

bool solve(int *board, unsigned long long *counter)
{
    return _solve(board, 0, 0, counter);
}

static inline void print_char(const int v)
{
    const char c = v == -1 ? 'x' : '0' + v;
    putchar(c);
}

void print_board(int *board, const bool borders)
{
    const size_t board_len = BOARDSIZE * BOARDSIZE;
    int j = 0;
    for (size_t i = 0; i < board_len; i++)
    {
        if (borders && i != 0 && i % (BOARDSIZE * 3) == 0)
            fputs("------+-------+------\n", stdout);
        if (borders && j != 0 && j % 3 == 0)
            fputs("| ", stdout);
        print_char(board[i]);
        if (j++ == BOARDSIZE - 1)
        {
            j = 0;
            putchar('\n');
        }
        else
            putchar(' ');
    }
}

char *err2str(const int errcode)
{
    if (errcode == 0)
        return "No error";
    switch (errcode)
    {
        case INVALID_LENGTH:
            return "Invalid board length, must be 81 characters long";
        case INVALID_CHARACTER:
            return "Invalid character in board. Valid characters are digits and empty characters can be any of \"x . 0\"";
        default:
            return "Unknown error";
    }
}
