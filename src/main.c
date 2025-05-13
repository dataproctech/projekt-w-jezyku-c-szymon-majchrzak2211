#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "../include/game_logic.h"
#include "../include/file_operation.h"

int main()
{
    Board board;
    char player = WHITE;
    int size = 8;
    initialize_board(&board, size);
    while(is_game_over(&board) == false)
    {
        player = (player == BLACK) ? WHITE : BLACK;
        print_board(&board);
        printf("Black: %d, White: %d\n", board.score.black_count, board.score.white_count);
        if (!has_valid_moves(&board, player)) 
        {
            printf("Player %c has no valid moves. Skipping turn.\n", player);
            continue;
        }
        int x, y;
        printf("Player %c, enter your move (e.g., A1): ", player);
        char col, command[4];
        scanf(" %s", command);
        col=command[0], y=command[1]-'0'; // Maybe it works
        if(strcmp(command, "save")==0){
            save(&board);
            player = (player == BLACK) ? WHITE : BLACK;
            continue;
        }
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
    if (board.score.black_count > board.score.white_count) 
        printf("Black wins!\n");
    else if (board.score.white_count > board.score.black_count) 
        printf("White wins!\n");
    else 
        printf("It's a draw!\n");
    printf("Final Score - Black: %d, White: %d\n",board.score.black_count, board.score.white_count);
    free_board(&board);
    return 0;
}    
