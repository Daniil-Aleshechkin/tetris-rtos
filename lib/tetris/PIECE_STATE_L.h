#include "TETRIS_ENUMS.h"

#ifndef PIECE_STATE_L
#define PIECE_STATE_L

// Constants for the L piece in the 0-degree rotation
// Sketch:
// o o x
// x x x
// o o o
const Position PIECE_L_0[4] = {
{2, 0}, {0, 1}, {1, 1}, {2, 1},
};

// Constants for the L piece in the 90-degree rotation
// Sketch:
// o x o
// o x o
// o x x
const Position PIECE_L_90[4] = {
{1, 0}, {1, 1}, {1, 2}, {2, 2},
};

// Constants for the L piece in the 180-degree rotation
// Sketch:
// o o o
// x x x
// x o o
const Position PIECE_L_180[4] = {
{0, 1}, {1, 1}, {0, 2}, {2, 1},
};

// Constants for the L piece in the 270-degree rotation
// Sketch:
// x x o
// o x o
// o x o
const Position PIECE_L_270[4] = {
{0, 0}, {1, 0}, {1, 1}, {1, 2},
};

Position* getLPieceByRotation(Rotation rotation);
#endif