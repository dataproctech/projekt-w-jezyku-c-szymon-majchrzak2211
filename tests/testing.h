#include <stdbool.h>

struct position{
    int x : 3;
    int y : 3;
};

struct pawn {
    struct position position;
    bool color; // 0 for white, 1 for black
    bool on_board;
};