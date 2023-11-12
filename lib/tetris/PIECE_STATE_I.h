#include "TETRIS_ENUMS.h"

#ifndef PIECE_STATE_I
#define PIECE_STATE_I

// Constants for the I piece in the 0-degree rotation
// Sketch:
// o o o o
// x x x x
// o o o o
// o o o o
const Position PIECE_I_0[4] = {
{0, 1}, {1, 1}, {2, 1}, {3, 1},
};

// Constants for the I piece in the 90-degree rotation
// Sketch:
// o o x o
// o o x o
// o o x o
// o o x o
const Position PIECE_I_90[4] = {
{2, 0}, {2, 1}, {2, 2}, {2, 3},
};

// Constants for the I piece in the 180-degree rotation
// Sketch:
// o o o o
// o o o o
// x x x x
// o o o o
const Position PIECE_I_180[4] = {
{0, 2}, {1, 2}, {2, 2}, {3, 2},
};

// Constants for the I piece in the 270-degree rotation
// o x o o
// o x o o
// o x o o
// o x o o
const Position PIECE_I_270[4] = {
{1, 0}, {1, 1}, {1, 2}, {1, 3},
};


Position* getIPieceByRotation(Rotation rotation);
#endif