#ifndef GUI_H
#define GUI_H

#include "game_logic.h"
#include "file_operation.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#define SQUARE_SIZE 50
#define SCORE_HEIGHT 40
#define DISPLAY_WIDTH SQUARE_SIZE * BOARD_SIZE 
#define DISPLAY_HEIGHT SQUARE_SIZE * BOARD_SIZE + SCORE_HEIGHT + BUTTON_SAVE_H + 100
#define FONT_LOCATION "assets/StarJediOutline-y0xm.ttf"
#define BUTTON_SAVE_X 10
#define BUTTON_SAVE_Y 470
#define BUTTON_SAVE_W 100
#define BUTTON_SAVE_H 40
#define BUTTON_LOAD_X 10
#define BUTTON_LOAD_Y 520
#define BUTTON_LOAD_W 100
#define BUTTON_LOAD_H 40
#define SLOTS_X 180
#define SLOTS_Y 480
#define SLOTS_W 90
#define SLOTS_H 40
#define SLOT_ACTIVE_COLOR al_map_rgb(50, 128, 50)
#define SLOT_INACTIVE_COLOR al_map_rgb(70, 70, 200)

int check_allegro();

int random_int(int min, int max);

int check_allegro_var(
    ALLEGRO_DISPLAY *display
);

int draw_frame(
    Board *board,
    char player,
    int slot
);

int make_a_move(
    Board *board,
    char *player,
    int mouse_x1,
    int mouse_y1,
    int mouse_x2,
    int mouse_y2
);

bool is_mouse_over_button_save(
    int mouse_x,
    int mouse_y
);

bool is_mouse_over_button_load(
    int mouse_x,
    int mouse_y
);

bool is_mouse_over_slots(
    int mouse_x,
    int mouse_y
);

int get_slot_from_mouse(
    int mouse_x,
    int mouse_y
);

#endif