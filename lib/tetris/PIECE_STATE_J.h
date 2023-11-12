#include "TETRIS_ENUMS.h"

#ifndef PIECE_STATE_J
#define PIECE_STATE_J

// Constants for the J piece in the 0-degree rotation
// Sketch:
// x o o
// x x x
// o o o
const Position PIECE_J_0[4] = {
{0, 0}, {0, 1}, {1, 1}, {2, 1},
};

// Constants for the J piece in the 90-degree rotation
// Sketch:
// o x x
// o x o
// o x o
const Position PIECE_J_90[4] = {
{1, 0}, {1, 1}, {1, 2}, {2, 0},
};

// Constants for the J piece in the 180-degree rotation
// Sketch:
// o o o
// x x x
// o o x
const Position PIECE_J_180[4] = {
{2, 1}, {1, 1}, {0, 1}, {2, 2},
};

// Constants for the J piece in the 270-degree rotation
// Sketch:
// o x o
// o x o
// x x o
const Position PIECE_J_270[4] = {
{1, 0}, {1, 1}, {1, 2}, {0, 2},
};

Position* getJPieceByRotation(Rotation rotation);
#endif