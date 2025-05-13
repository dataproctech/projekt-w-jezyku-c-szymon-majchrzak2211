#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include "game_logic.h"
#include <stdlib.h>
#include <string.h>

int save(Board *board);
int check_saves();
char *get_save_name();
#endif