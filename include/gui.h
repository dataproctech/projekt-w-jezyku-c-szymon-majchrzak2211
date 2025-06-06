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
#define DISPLAY_HEIGHT SQUARE_SIZE * BOARD_SIZE + SCORE_HEIGHT
#define FONT_LOCATION "assets/StarJediOutline-y0xm.ttf"

int check_allegro();

int random_int(int min, int max);

int check_allegro_var(
    ALLEGRO_DISPLAY *display
);

int draw_frame(
    Board *board,
    char player
);

int make_a_move(
    Board *board,
    char *player,
    int mouse_x1,
    int mouse_y1,
    int mouse_x2,
    int mouse_y2
);

#endif