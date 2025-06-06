#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define EMPTY '.'
#define BLACK 'B'
#define WHITE 'W'
#define BOARD_SIZE 8
#include <stdbool.h>

typedef struct
{
    int black_count;
    int white_count;
} str_score;

typedef struct 
{
    int size;
    str_score score;
    char **board;
} Board;

void initialize_board(Board *board, int size);
void count_pieces(Board *board, int *black_count, int *white_count);
void print_board(Board *board);
void free_board(Board *board);

bool is_valid_move(Board *board, int x, int y, char player);
void flipcolor(Board *board, int x, int y, char player);
bool apply_move(Board *board, int x, int y, char player);
bool has_valid_moves(Board *board, char player);
bool is_game_over(Board *board);

#endif