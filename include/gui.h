#ifndef GUI_H
#define GUI_H

#include "game_logic.h"
#include "file_operation.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdbool.h>

#define SQUARE_SIZE 50
#define SCORE_HEIGHT 40
#define FONT_LOCATION "assets/StarJediOutline-y0xm.ttf"

int check_allegro();

int check_allegro_var(
    ALLEGRO_DISPLAY *display
);

int draw_frame(
    Board *board
);

#endif