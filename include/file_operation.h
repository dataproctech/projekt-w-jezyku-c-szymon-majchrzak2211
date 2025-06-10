#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include "game_logic.h"
#include <stdlib.h>
#include <string.h>

int save(Board *board, char turn, int slot);
int load(Board *board, int slot);
void check_saves();
char *get_save_name();

#endif