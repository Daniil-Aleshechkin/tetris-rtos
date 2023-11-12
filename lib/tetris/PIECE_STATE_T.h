#include "TETRIS_ENUMS.h"

#ifndef PIECE_STATE_T
#define PIECE_STATE_T

// Constants for the T piece in the 0-degree rotation
// Sketch:
// o x o
// x x x
// o o o
const Position PIECE_T_0[4] = {
{0, 1}, {1, 0}, {1, 1}, {2, 1},
};

// Constants for the T piece in the 90-degree rotation
// Sketch:
// o x o
// o x x
// o x o
const Position PIECE_T_90[4] = {
{1, 0}, {1, 1}, {1, 2}, {2, 1},
};

// Constants for the T piece in the 180-degree rotation
// Sketch:
// o o o
// x x x
// o x o
const Position PIECE_T_180[4] = {
{0, 1}, {1, 1}, {1, 2}, {2, 1},
};

// Constants for the T piece in the 270-degree rotation
// Sketch:
// o x o
// x x o
// o x o
const Position PIECE_T_270[4] = {
{0, 1}, {1, 0}, {1, 1}, {1, 2},
};

Position* getTPieceByRotation(Rotation rotation);
#endif