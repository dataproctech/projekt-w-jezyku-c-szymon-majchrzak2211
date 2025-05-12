#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/game_logic.h"

int main()
{
    Board board;
    char player = BLACK;
    int size = 8;
    initialize_board(&board, size);
    while(1)
    {
        print_board(&board);
        player = (player == BLACK) ? WHITE : BLACK;
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
    return 0;
}    
