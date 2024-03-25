/**
 * @file PIECE_STATE_I.h
 * @brief Defines the rotation states for the Tetris "I" piece.
 *
 * This header file contains the definitions of the Tetris "I" piece's layout
 * for each of its four possible rotations (0, 90, 180, and 270 degrees).
 * Additionally, it declares a function for retrieving the "I" piece's layout
 * based on its current rotation.
 */

#include "TETRIS_ENUMS.h"

#ifndef PIECE_STATE_I
#define PIECE_STATE_I

/**
 * @brief Positions for the "I" piece in a 0-degree rotation.
 *
 * Represents the "I" piece's layout when it has not been rotated.
 * The layout is visualized as follows, with 'x' marking the occupied cells:
 *
 * o o o o
 * x x x x
 * o o o o
 * o o o o
 */
const Position PIECE_I_0[4] = {
{0, 1}, {1, 1}, {2, 1}, {3, 1},
};

/**
 * @brief Positions for the "I" piece in a 90-degree rotation.
 *
 * Represents the "I" piece's layout when it is rotated 90 degrees clockwise.
 * The layout is visualized as follows:
 *
 * o o x o
 * o o x o
 * o o x o
 * o o x o
 */
const Position PIECE_I_90[4] = {
{2, 0}, {2, 1}, {2, 2}, {2, 3},
};

/**
 * @brief Positions for the "I" piece in a 180-degree rotation.
 *
 * Represents the "I" piece's layout when it is rotated 180 degrees.
 * The layout is visualized as follows:
 *
 * o o o o
 * o o o o
 * x x x x
 * o o o o
 */
const Position PIECE_I_180[4] = {
{0, 2}, {1, 2}, {2, 2}, {3, 2},
};

/**
 * @brief Positions for the "I" piece in a 270-degree rotation.
 *
 * Represents the "I" piece's layout when it is rotated 270 degrees clockwise.
 * The layout is visualized as follows:
 *
 * o x o o
 * o x o o
 * o x o o
 * o x o o
 */
const Position PIECE_I_270[4] = {
{1, 0}, {1, 1}, {1, 2}, {1, 3},
};

/**
 * @brief Retrieves the positions of the "I" piece for a given rotation.
 *
 * @param rotation The rotation angle (0, 90, 180, 270) of the "I" piece.
 * @return A pointer to the array of Position structs representing the "I" piece's layout for the given rotation.
 */
Position* getIPieceByRotation(Rotation rotation);
#endif