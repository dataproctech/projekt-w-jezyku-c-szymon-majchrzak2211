#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/game_logic.h"

int main()
{
    Board board;
    char player = WHITE;
    int size = 8;
    int black_count, white_count;
    initialize_board(&board, size);
    while(is_game_over(&board) == false)
    {
        player = (player == BLACK) ? WHITE : BLACK;
        print_board(&board);
        count_pieces(&board, &black_count, &white_count);
        printf("Black: %d, White: %d\n", black_count, white_count);
        if (!has_valid_moves(&board, player)) 
        {
            printf("Player %c has no valid moves. Skipping turn.\n", player);
            continue;
        }
        int x, y;
        printf("Player %c, enter your move (e.g., A1): ", player);
        char col;
        scanf(" %c%d", &col, &y);
        x = toupper(col) - 'A';
        y -= 1; // Adjust for 0-based index
        while(apply_move(&board, x, y, player) == false)
        {
            printf("Invalid move. Try again: ");
            scanf(" %c%d", &col, &y);
            x = toupper(col) - 'A';
            y -= 1; // Adjust for 0-based index
        }
    }
    print_board(&board);
    count_pieces(&board, &black_count, &white_count);
    if (black_count > white_count) 
        printf("Black wins!\n");
    else if (white_count > black_count) 
        printf("White wins!\n");
    else 
        printf("It's a draw!\n");
    printf("Final Score - Black: %d, White: %d\n", black_count, white_count);
    free_board(&board);
    return 0;
}    
