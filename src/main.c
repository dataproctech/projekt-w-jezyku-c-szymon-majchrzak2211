#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "../include/game_logic.h"
#include "../include/file_operation.h"
#include "../include/gui.h"

void old_terminal_version(){
    Board board;
    char player = WHITE;
    const int size = BOARD_SIZE;
    int tmp;
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
            save(&board, player);
            player = (player == BLACK) ? WHITE : BLACK;
            continue;
        }
        else if(strcmp(command, "load")==0){
            tmp = load(&board);
            if(tmp==-1){
                printf("Error: Couldn't load a save\n");
            }
            else{
                player = (tmp == BLACK) ? WHITE : BLACK;
            }
            continue;
        }
        x = toupper(col) - 'A';
        y -= 1; // Adjust for 0-based index
        while(apply_move(&board, x, y, player) == false)
        {
            printf("Invalid move. Try again: ");
            scanf(" %s", command);
            col=command[0], y=command[1]-'0'; // Maybe it works
            if(strcmp(command, "save")==0){
                save(&board, player);
                continue;
            }
            else if(strcmp(command, "load")==0){
                tmp = load(&board);
                if(tmp==-1){
                    printf("Error: Couldn't load a save\n");
                }
                else{
                    player = tmp;
                }
                continue;
            }
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
}

int main()
{
    if(check_allegro()==-1) return -1;
    ALLEGRO_DISPLAY *display = al_create_display(SQUARE_SIZE * BOARD_SIZE, SQUARE_SIZE * BOARD_SIZE + SCORE_HEIGHT);
    if(check_allegro_var(display)==-1) return -1;

    ALLEGRO_EVENT_QUEUE *queueue = al_create_event_queue();
    al_register_event_source(queueue, al_get_display_event_source(display));


    Board board;
    initialize_board(&board, BOARD_SIZE);
    char player = WHITE;
    bool running = true;

    
    draw_frame(&board);

    while(running){
        ALLEGRO_EVENT eevee;
        al_wait_for_event(queueue, &eevee);

        if(eevee.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
        }

        draw_frame(&board);
        al_flip_display();
    }
    
    free_board(&board);
    al_destroy_event_queue(queueue);
    al_destroy_display(display);
    al_uninstall_system();
    return 0;
}    
