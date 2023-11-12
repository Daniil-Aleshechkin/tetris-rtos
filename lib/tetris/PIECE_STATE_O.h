#include "TETRIS_ENUMS.h"


#ifndef PIECE_STATE_O
#define PIECE_STATE_O

// Constants for the O piece in all rotations (O piece does not rotate)
// Sketch:
// x x
// x x
const Position PIECE_O[4] = {
{0, 0}, {1, 0}, {0, 1}, {1, 1}
};

#endif