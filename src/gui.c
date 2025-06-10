#include "../include/gui.h"

int random_int(int min, int max){
    return rand() % (max - min + 1) + min;
}

int check_allegro(){
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro\n");
        return -1;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Failed to initialize primitives addon\n");
        return -1;
    }

    if (!al_init_font_addon() || !al_init_ttf_addon()) {
        fprintf(stderr, "Failed to initialize font addons\n");
        return -1;
    }
    return 0;
}
int check_allegro_var(ALLEGRO_DISPLAY *var){
    if (!var) {
        fprintf(stderr, "Failed to create display\n");
        return -1;
    }
    return 0;
}

void draw_pawn(ALLEGRO_COLOR pawn_color, int col, int row){ // might make an animation later or something
    al_draw_filled_circle((col+0.5)*SQUARE_SIZE, (row+0.5)*SQUARE_SIZE + SCORE_HEIGHT, SQUARE_SIZE/3, pawn_color);
}
void draw_moves(ALLEGRO_COLOR available_move_color, int col, int row){ // placeholder for now
    al_draw_filled_triangle(
        (col+0.5)*SQUARE_SIZE, (row+0.115)*SQUARE_SIZE+SCORE_HEIGHT,
        (col+0.833)*SQUARE_SIZE, (row+0.692)*SQUARE_SIZE+SCORE_HEIGHT,
        (col+0.167)*SQUARE_SIZE, (row+0.692)*SQUARE_SIZE+SCORE_HEIGHT,
        available_move_color
        );
}

int draw_frame(Board *board, char player, int slot){
    // Clear background
    al_clear_to_color(al_map_rgb(240, 240, 240));
    // Draw score area background
    al_draw_filled_rectangle(0, 0, BOARD_SIZE * SQUARE_SIZE, SCORE_HEIGHT, al_map_rgb(20, 20, 25));
    
    // Set the font
    ALLEGRO_FONT *font = al_load_ttf_font(FONT_LOCATION, 24, 0);
    if (!font) { fprintf(stderr, "Failed to load font\n"); return -1;}
    // Draw score text
    char score_text_white[32], score_text_black[32];
    snprintf(score_text_black, sizeof(score_text_black), "Black: %d", board->score.black_count);
    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 5, 0, score_text_black);
    snprintf(score_text_white, sizeof(score_text_white), "Red: %d", board->score.white_count);
    al_draw_text(font, al_map_rgb(255, 255, 255), BOARD_SIZE*SQUARE_SIZE-125, 5, 0, score_text_white);

    //Draw Buttons and slots
    al_draw_filled_rectangle(0,BOARD_SIZE * SQUARE_SIZE + SCORE_HEIGHT,
                                DISPLAY_WIDTH, DISPLAY_HEIGHT, 
                                al_map_rgb(20, 20, 25));
        
    al_draw_filled_rectangle(BUTTON_SAVE_X, BUTTON_SAVE_Y,
                                BUTTON_SAVE_X + BUTTON_SAVE_W, BUTTON_SAVE_Y + BUTTON_SAVE_H,
                                al_map_rgb(70, 70, 200));                            
    al_draw_text(font, al_map_rgb(255, 255, 255),
                    BUTTON_SAVE_X + BUTTON_SAVE_W / 2,
                    BUTTON_SAVE_Y,
                    ALLEGRO_ALIGN_CENTER, "Save");

    al_draw_filled_rectangle(BUTTON_LOAD_X, BUTTON_LOAD_Y,
                                BUTTON_LOAD_X + BUTTON_LOAD_W, BUTTON_LOAD_Y + BUTTON_LOAD_H,
                                al_map_rgb(70, 70, 200));
    al_draw_text(font, al_map_rgb(255, 255, 255),
                    BUTTON_LOAD_X + BUTTON_LOAD_W / 2,
                    BUTTON_LOAD_Y,
                    ALLEGRO_ALIGN_CENTER, "Load");
    
    al_draw_text(font, al_map_rgb(255,255,255),
                    SLOTS_X+50 + SLOTS_W / 2,
                    SLOTS_Y - 40,
                    ALLEGRO_ALIGN_CENTER, "Slots");

    ALLEGRO_COLOR slot_color = (slot == 1) ? SLOT_ACTIVE_COLOR : SLOT_INACTIVE_COLOR;
    al_draw_filled_rectangle(SLOTS_X, SLOTS_Y,
                                SLOTS_X + SLOTS_W, SLOTS_Y + SLOTS_H,
                                slot_color);

    
    al_draw_text(font, al_map_rgb(255, 255, 255),
                    SLOTS_X + SLOTS_W / 2,
                    SLOTS_Y,
                    ALLEGRO_ALIGN_CENTER, "1");

    slot_color = (slot == 2) ? SLOT_ACTIVE_COLOR : SLOT_INACTIVE_COLOR;
    al_draw_filled_rectangle(SLOTS_X+SLOTS_W+10, SLOTS_Y,
                                SLOTS_X+SLOTS_W+10 + SLOTS_W, SLOTS_Y + SLOTS_H,
                                slot_color);

    
    al_draw_text(font, al_map_rgb(255, 255, 255),
                    SLOTS_X+SLOTS_W+10 + SLOTS_W / 2,
                    SLOTS_Y,
                    ALLEGRO_ALIGN_CENTER, "2");
    
    slot_color = (slot == 3) ? SLOT_ACTIVE_COLOR : SLOT_INACTIVE_COLOR;
     al_draw_filled_rectangle(SLOTS_X, SLOTS_Y+SLOTS_H+10,
                                SLOTS_X + SLOTS_W, SLOTS_Y+SLOTS_H+10 + SLOTS_H,
                                slot_color);

    
    al_draw_text(font, al_map_rgb(255, 255, 255),
                    SLOTS_X + SLOTS_W / 2,
                    SLOTS_Y + SLOTS_H + 10,
                    ALLEGRO_ALIGN_CENTER, "3");

    slot_color = (slot == 4) ? SLOT_ACTIVE_COLOR : SLOT_INACTIVE_COLOR;
    al_draw_filled_rectangle(SLOTS_X+SLOTS_W+10, SLOTS_Y+SLOTS_H+10,
                                SLOTS_X+SLOTS_W+10 + SLOTS_W, SLOTS_Y+SLOTS_H+10 + SLOTS_H,
                                slot_color);

    
    al_draw_text(font, al_map_rgb(255, 255, 255),
                    SLOTS_X+SLOTS_W+10 + SLOTS_W / 2,
                    SLOTS_Y + SLOTS_H + 10,
                    ALLEGRO_ALIGN_CENTER, "4");

    // Draw the 8x8 board starting below the score
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            bool is_light_square = (row + col) % 2 == 0;
            ALLEGRO_COLOR color = is_light_square ? al_map_rgb(60, 60, 60) : al_map_rgb(160, 160, 160);
            al_draw_filled_rectangle(
                col * SQUARE_SIZE,
                SCORE_HEIGHT + row * SQUARE_SIZE,
                (col + 1) * SQUARE_SIZE,
                SCORE_HEIGHT + (row + 1) * SQUARE_SIZE,
                color
            );
            ALLEGRO_COLOR pawn_color;
            bool is_draw_pawn=false;
            switch(board->board[row][col]){
                case('B'):
                    pawn_color = al_map_rgb(20, 20, 20);
                    is_draw_pawn=true;
                    break;
                case('W'):
                    pawn_color = al_map_rgb(180, 40, 60);
                    is_draw_pawn=true;
                    break;
            }
            if(is_draw_pawn){
                draw_pawn(pawn_color, col, row);
            }
            else if(is_valid_move(board, col, row, player)){
                draw_moves(al_map_rgb(20, 20, 90), col, row);
            }
        }
    }

    al_flip_display();
    al_destroy_font(font);
}

int make_a_move(Board *board, char *player, int mouse_x1, int mouse_y1, int mouse_x2, int mouse_y2){
    int row = (mouse_y1 - SCORE_HEIGHT)/SQUARE_SIZE;
    int col = mouse_x1 / SQUARE_SIZE;
    int row2 = (mouse_y2 - SCORE_HEIGHT)/SQUARE_SIZE;
    int col2 = mouse_x2 / SQUARE_SIZE;
    printf("col: %d row:%d\n", col, row);
    al_draw_circle(100, 100, 50, al_map_rgb(255,255,255),5);
    if(row!=row2 || col!=col2) return -1;
    if(!is_valid_move(board, col, row, *player)) return -2;

    apply_move(board, col, row, *player);
    *player = (*player == BLACK) ? WHITE : BLACK;
}

bool is_mouse_over_button_save(int mouse_x, int mouse_y) {
    return mouse_x >= BUTTON_SAVE_X && mouse_x <= BUTTON_SAVE_X + BUTTON_SAVE_W &&
           mouse_y >= BUTTON_SAVE_Y && mouse_y <= BUTTON_SAVE_Y + BUTTON_SAVE_H;
}

bool is_mouse_over_button_load(int mouse_x, int mouse_y) {
    return mouse_x >= BUTTON_LOAD_X && mouse_x <= BUTTON_LOAD_X + BUTTON_LOAD_W &&
           mouse_y >= BUTTON_LOAD_Y && mouse_y <= BUTTON_LOAD_Y + BUTTON_LOAD_H;
}
bool is_mouse_over_slots(int mouse_x, int mouse_y) {
    return mouse_x >= SLOTS_X && mouse_x <= SLOTS_X + 2 * (SLOTS_W + 10) &&
           mouse_y >= SLOTS_Y && mouse_y <= SLOTS_Y + 2 * (SLOTS_H + 10);
}

bool choose_slot(int mouse_x, int mouse_y, int slot) {
    int slot_x = SLOTS_X + (slot % 2) * (SLOTS_W + 10);
    int slot_y = SLOTS_Y + (slot / 2) * (SLOTS_H + 10);
    return mouse_x >= slot_x && mouse_x <= slot_x + SLOTS_W &&
           mouse_y >= slot_y && mouse_y <= slot_y + SLOTS_H;
}
int get_slot_from_mouse(int mouse_x, int mouse_y) {
    for (int slot = 0; slot < 4; slot++) {
        if (choose_slot(mouse_x, mouse_y, slot)) {
            printf("Slot %d clicked\n", slot + 1);
            // Return the slot number (1-4)
            return slot+1;
        }
    }
    return -1; // No valid slot clicked
}
