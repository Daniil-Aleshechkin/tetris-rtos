#include "TETRIS_ENUMS.h"

#ifndef PIECE_STATE_Z
#define PIECE_STATE_Z

// Constants for the Z piece in the 0-degree rotation
// Sketch:
// x x o
// o x x
// o o o
const Position PIECE_Z_0[4] = {
{0, 0}, {1, 0}, {1, 1}, {2, 1},
};

// Constants for the Z piece in the 90-degree rotation
// Sketch:
// o o x
// o x x
// o x o
const Position PIECE_Z_90[4] = {
{2, 0}, {1, 1}, {1, 2}, {2, 1},
};

// Constants for the Z piece in the 180-degree rotation
// Sketch:
// o o o
// x x o
// o x x
const Position PIECE_Z_180[4] = {
{0, 1}, {1, 1}, {2, 2}, {1, 2},
};

// Constants for the Z piece in the 270-degree rotation
// Sketch:
// o x o
// x x o
// x o o
const Position PIECE_Z_270[4] = {
{0, 1}, {1, 0}, {1, 1}, {0, 2},
};


// Function declarations for getting the Z piece by rotation
Position* getZPieceByRotation(Rotation rotation);
#endif