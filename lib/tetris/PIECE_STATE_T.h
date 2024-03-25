/**
 * @file PIECE_STATE_T.h
 * @brief Defines the rotation states for the Tetris "T" piece.
 *
 * This header file contains the definitions for the layout of the Tetris "T" piece
 * for each of its four possible rotations (0, 90, 180, and 270 degrees). It also
 * declares a function for retrieving the "T" piece's layout based on its current
 * rotation, facilitating its placement and movement on the game board.
 */

#ifndef PIECE_STATE_T
#define PIECE_STATE_T

#include "TETRIS_ENUMS.h"

/**
 * @brief Positions for the "T" piece in a 0-degree rotation.
 *
 * Represents the "T" piece's layout when it has not been rotated. The layout
 * is visualized as follows, with 'x' marking the occupied cells:
 *
 * o x o
 * x x x
 * o o o
 */
const Position PIECE_T_0[4] = {
{1, 1}, {0, 1}, {2, 1}, {1, 0},
};

/**
 * @brief Positions for the "T" piece in a 90-degree rotation.
 *
 * Represents the "T" piece's layout when it is rotated 90 degrees clockwise.
 * The layout is visualized as follows:
 *
 * o x o
 * o x x
 * o x o
 */
const Position PIECE_T_90[4] = {
{1, 0}, {1, 1}, {1, 2}, {2, 1},
};

/**
 * @brief Positions for the "T" piece in a 180-degree rotation.
 *
 * Represents the "T" piece's layout when it is rotated 180 degrees. The layout
 * is visualized as follows:
 *
 * o o o
 * x x x
 * o x o
 */
const Position PIECE_T_180[4] = {
{1, 2}, {0, 1}, {1, 1}, {2, 1},
};

/**
 * @brief Positions for the "T" piece in a 270-degree rotation.
 *
 * Represents the "T" piece's layout when it is rotated 270 degrees clockwise.
 * The layout is visualized as follows:
 *
 * o x o
 * x x o
 * o x o
 */
const Position PIECE_T_270[4] = {
{1, 0}, {0, 1}, {1, 1}, {1, 2},
};

/**
 * @brief Retrieves the positions of the "T" piece for a given rotation.
 *
 * @param rotation The rotation angle (0, 90, 180, 270) of the "T" piece.
 * @return A pointer to the array of Position structs representing the "T" piece's layout for the given rotation.
 */
Position* getTPieceByRotation(Rotation rotation);

#endif /* PIECE_STATE_T */
