#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "../include/game_logic.h"
#include "../include/file_operation.h"
#include "../include/gui.h"
/*
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
}*/

int main()
{
    
    if(check_allegro()==-1) return -1;
    ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if(check_allegro_var(display)==-1) return -1;

    ALLEGRO_EVENT_QUEUE *queueue = al_create_event_queue();
    al_register_event_source(queueue, al_get_display_event_source(display));
    bool keyboard_install = !al_is_keyboard_installed();
    if(keyboard_install) al_install_keyboard();
    al_register_event_source(queueue, al_get_keyboard_event_source());
    bool mouse_install = !al_is_mouse_installed();
    if(mouse_install) al_install_mouse();
    al_register_event_source(queueue, al_get_mouse_event_source());
    

    Board board;
    initialize_board(&board, BOARD_SIZE);
    char player = WHITE;
    bool running = true;
    int x1, y1, x2, y2;
    int click_stage=0;
    int slot;
    draw_frame(&board, player,slot);

    while(running){
        ALLEGRO_EVENT eevee;
        ALLEGRO_KEYBOARD_STATE keyboard;
        if(has_valid_moves(&board, player) == false){
            printf("Player %c has no valid moves. Skipping turn.\n", player);
            player = (player == BLACK) ? WHITE : BLACK;
            draw_frame(&board, player, slot);
            al_flip_display();
        }
        al_wait_for_event(queueue, &eevee);
        al_get_keyboard_state(&keyboard);

        if(eevee.type == ALLEGRO_EVENT_DISPLAY_CLOSE || (eevee.type == ALLEGRO_EVENT_KEY_DOWN && al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))||is_game_over(&board)){
            running = false;
        }
        else if(eevee.type == ALLEGRO_EVENT_DISPLAY_RESIZE){ // just some fun stuff
            int x, y;
            al_get_window_position(display, &x, &y);
            al_resize_display(display, DISPLAY_WIDTH, DISPLAY_HEIGHT);
            al_toggle_display_flag(display, ALLEGRO_MAXIMIZED, false);
            al_set_window_position(display,x+random_int(20, 50), y+random_int(20, 50));
        }
        else if(eevee.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            printf("Hello\n");
            x1=eevee.mouse.x;
            y1=eevee.mouse.y;
            click_stage=1;
        }
        else if(eevee.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && click_stage == 1){
            printf("There\n");
            if(is_mouse_over_button_save(eevee.mouse.x, eevee.mouse.y)){
                printf("Save\n");
                save(&board, player, slot); 
                click_stage=0;
            }
            else if(is_mouse_over_button_load(eevee.mouse.x, eevee.mouse.y)){
                printf("Load\n");
                player=load(&board, slot);
                click_stage=0;
            }
            else if(is_mouse_over_slots(eevee.mouse.x, eevee.mouse.y)){
                slot = get_slot_from_mouse(eevee.mouse.x, eevee.mouse.y);
                printf("Slot: %d\n", slot);
                click_stage=0;
            }
            else{
            x2=eevee.mouse.x;
            y2=eevee.mouse.y;
            make_a_move(&board, &player, x1, y1, x2, y2);
            click_stage=0;
            }
        }
        
        
        draw_frame(&board, player, slot);
        al_flip_display();
    }
    
    bool done = false;
    while(!done)
    {
        ALLEGRO_FONT *font = al_load_ttf_font(FONT_LOCATION, 24, 0);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(255, 0, 0), 200, 200,
                     ALLEGRO_ALIGN_CENTER, "game over");
        if (board.score.black_count > board.score.white_count) {
            al_draw_text(font, al_map_rgb(255, 255, 255), 200, 250,
                         ALLEGRO_ALIGN_CENTER, "Black wins!");
        } else if (board.score.white_count > board.score.black_count) {
            al_draw_text(font, al_map_rgb(255, 255, 255), 200, 250,
                         ALLEGRO_ALIGN_CENTER, "Red wins!");
        } else {
            al_draw_text(font, al_map_rgb(255, 255, 255), 200, 250,
                         ALLEGRO_ALIGN_CENTER, "it's a draw!");
        }
        char score_text[64];
        snprintf(score_text, sizeof(score_text), "Black: %d, Red: %d",
                 board.score.black_count, board.score.white_count);
        al_draw_text(font, al_map_rgb(255, 255, 255), 200, 280,
                     ALLEGRO_ALIGN_CENTER, score_text);
        al_draw_text(font, al_map_rgb(255, 255, 255), 200, 330,
                     ALLEGRO_ALIGN_CENTER, "Press any key to quit...");
        al_flip_display();

        ALLEGRO_EVENT eevee;
        ALLEGRO_KEYBOARD_STATE keyboard;
        al_wait_for_event(queueue, &eevee);

        if (eevee.type == ALLEGRO_EVENT_DISPLAY_CLOSE ||
            eevee.type == ALLEGRO_EVENT_KEY_DOWN) {
            done = true;
        }
    }
    free_board(&board);
    al_destroy_event_queue(queueue);
    al_destroy_display(display);
    if(keyboard_install) al_uninstall_keyboard();
    if(mouse_install) al_uninstall_mouse();
    al_uninstall_system();
    return 0;
}    
