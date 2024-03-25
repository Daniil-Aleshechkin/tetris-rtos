/**
 * @file PIECE_STATE_O.h
 * @brief Defines the static state for the Tetris "O" piece.
 *
 * This header file contains the definition for the layout of the Tetris "O" piece.
 * The "O" piece is unique in that it does not change its orientation with rotation.
 * The layout is a 2x2 square, which remains constant regardless of rotation commands.
 */

#ifndef PIECE_STATE_O
#define PIECE_STATE_O

#include "TETRIS_ENUMS.h"

/**
 * @brief Positions for the "O" piece in all rotations.
 *
 * Represents the "O" piece's layout, which does not change with rotation. The layout
 * is visualized as follows, with 'x' marking the occupied cells:
 *
 * x x
 * x x
 *
 * Since the "O" piece does not rotate, these positions are used for all rotations.
 */
const Position PIECE_O[4] = {
{0, 0}, {1, 0}, {0, 1}, {1, 1}
};

#endif /* PIECE_STATE_O */
