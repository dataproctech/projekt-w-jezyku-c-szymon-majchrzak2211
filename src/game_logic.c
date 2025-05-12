#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "game_logic.h"

void initialize_board(Board *board, int size) 
{
    board->size = size;
    board->board = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        board->board[i] = malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            board->board[i][j] = EMPTY;
        }
    }
    int mid = size / 2;
    board->board[mid - 1][mid - 1] = WHITE;
    board->board[mid][mid] = WHITE;
    board->board[mid - 1][mid] = BLACK;
    board->board[mid][mid - 1] = BLACK;
}

void count_pieces(Board *board, int *black_count, int *white_count) 
{
    *black_count = 0;
    *white_count = 0;
    for (int i = 0; i < board->size; i++) 
        for (int j = 0; j < board->size; j++) 
            if (board->board[i][j] == BLACK) 
                (*black_count)++;
             else if (board->board[i][j] == WHITE) 
                (*white_count)++;
}
void print_board(Board *board) 
{
    printf("  ");
    for (int i = 0; i < board->size; i++) 
        printf("%c ", 'A' + i);
    
    printf("\n");
    for (int i = 0; i < board->size; i++) 
    {
        printf("%d ", i + 1);
        for (int j = 0; j < board->size; j++) 
            printf("%c ", board->board[i][j]);
        printf("\n");
    }
}

void free_board(Board *board) 
{
    for (int i = 0; i < board->size; i++) {
        free(board->board[i]);
    }
    free(board->board);
}

bool is_valid_move(Board *board, int x, int y, char player) 
{
    if (x < 0 || x >= board->size || y < 0 || y >= board->size || board->board[x][y] != EMPTY) 
        return false;

    char opponent = (player == BLACK) ? WHITE : BLACK;
    bool valid = false;

    // Check all 8 directions
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip the current position
            int nx = x + dx;
            int ny = y + dy;
            bool found_opponent = false;

            while (nx >= 0 && nx < board->size && ny >= 0 && ny < board->size) {
                if (board->board[ny][nx] == opponent) {
                    found_opponent = true;
                } else if (board->board[ny][nx] == player) {
                    if (found_opponent) {
                        valid = true;
                    }
                    break;
                } else {
                    break;
                }
                nx += dx;
                ny += dy;
            }
        }
    }
    return valid;
}

void flipcolor(Board *board, int x, int y, char player) 
{
    char opponent = (player == BLACK) ? WHITE : BLACK;

    // Check all 8 directions
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip the current position
            int nx = x + dx;
            int ny = y + dy;
            bool found_opponent = false;

            while (nx >= 0 && nx < board->size && ny >= 0 && ny < board->size) {
                if (board->board[ny][nx] == opponent) {
                    found_opponent = true;
                } else if (board->board[ny][nx] == player) {
                    if (found_opponent) {
                        // Flip the opponent's pieces
                        while (nx != x || ny != y) {
                            nx -= dx;
                            ny -= dy;
                            board->board[ny][nx] = player;
                        }
                    }
                    break;
                } else {
                    break;
                }
                nx += dx;
                ny += dy;
            }
        }
    }
}

bool apply_move(Board *board, int x, int y, char player) 
{
    if (is_valid_move(board, x, y, player)) 
    {
        board->board[y][x] = player;
        flipcolor(board, x, y, player);
        return true;
    }
    return false;
}
