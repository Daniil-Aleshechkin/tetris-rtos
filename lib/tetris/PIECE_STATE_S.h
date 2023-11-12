#include "TETRIS_ENUMS.h"

#ifndef PIECE_STATE_S
#define PIECE_STATE_S

// Constants for the S piece in the 0-degree rotation
// Sketch:
// o x x
// x x o
// o o o
const Position PIECE_S_0[4] = {
{0, 1}, {2, 0}, {1, 0}, {1, 1},
};

// Constants for the S piece in the 90-degree rotation
// Sketch:
// o x o
// o x x
// o o x
const Position PIECE_S_90[4] = {
{1, 0}, {1, 1}, {2, 1}, {2, 2},
};

// Constants for the S piece in the 180-degree rotation
// Sketch:
// o o o
// o x x
// x x o
const Position PIECE_S_180[4] = {
{0, 2}, {1, 1}, {2, 1}, {1, 2},
};

// Constants for the S piece in the 270-degree rotation
// Sketch:
// x o o
// x x o
// o x o
const Position PIECE_S_270[4] = {
{0, 0}, {0, 1}, {1, 1}, {1, 2},
};

Position* getSPieceByRotation(Rotation rotation);
#endif