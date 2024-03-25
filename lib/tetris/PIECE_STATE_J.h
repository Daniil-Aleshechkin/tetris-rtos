/**
 * @file PIECE_STATE_J.h
 * @brief Defines the rotation states for the Tetris "J" piece.
 *
 * This header file contains the definitions for the layout of the Tetris "J" piece
 * for each of its four possible rotations (0, 90, 180, and 270 degrees). It also
 * declares a function for retrieving the "J" piece's layout based on its current
 * rotation, facilitating its placement and movement on the game board.
 */

#include "TETRIS_ENUMS.h"

#ifndef PIECE_STATE_J
#define PIECE_STATE_J

/**
 * @brief Positions for the "J" piece in a 0-degree rotation.
 *
 * Represents the "J" piece's layout when it has not been rotated. The layout
 * is visualized as follows, with 'x' marking the occupied cells:
 *
 * x o o
 * x x x
 * o o o
 */
const Position PIECE_J_0[4] = {
{0, 0}, {0, 1}, {1, 1}, {2, 1},
};

/**
 * @brief Positions for the "J" piece in a 90-degree rotation.
 *
 * Represents the "J" piece's layout when it is rotated 90 degrees clockwise.
 * The layout is visualized as follows:
 *
 * o x x
 * o x o
 * o x o
 */
const Position PIECE_J_90[4] = {
{1, 0}, {1, 1}, {1, 2}, {2, 0},
};

/**
 * @brief Positions for the "J" piece in a 180-degree rotation.
 *
 * Represents the "J" piece's layout when it is rotated 180 degrees. The layout
 * is visualized as follows:
 *
 * o o o
 * x x x
 * o o x
 */
const Position PIECE_J_180[4] = {
{2, 1}, {1, 1}, {0, 1}, {2, 2},
};

/**
 * @brief Positions for the "J" piece in a 270-degree rotation.
 *
 * Represents the "J" piece's layout when it is rotated 270 degrees clockwise.
 * The layout is visualized as follows:
 *
 * o x o
 * o x o
 * x x o
 */
const Position PIECE_J_270[4] = {
{1, 0}, {1, 1}, {1, 2}, {0, 2},
};

/**
 * @brief Retrieves the positions of the "J" piece for a given rotation.
 *
 * @param rotation The rotation angle (0, 90, 180, 270) of the "J" piece.
 * @return A pointer to the array of Position structs representing the "J" piece's layout for the given rotation.
 */
Position* getJPieceByRotation(Rotation rotation);
#endif