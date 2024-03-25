/**
 * @file BOARD_STATE_H.h
 * @brief Additional functionalities for Tetris game board management.
 * 
 * Extends the basic game board definitions with functionalities to retrieve the specific
 * configuration of Tetris pieces based on their type and rotation state.
 */

#include "BOARD_STATE_H.h"

/**
 * @brief Retrieves the positions of the blocks composing a Tetris piece for a given type and rotation.
 * 
 * This function calculates the positions of the individual blocks that compose a Tetris piece,
 * based on the piece's type and its rotation. This is essential for rendering the piece on the
 * game board, as well as for collision detection and piece placement.
 * 
 * @param type The type of the Tetris piece (e.g., PIECE_TYPE_I, PIECE_TYPE_T).
 * @param rotation The rotation state of the piece (e.g., DEG_0, DEG_90).
 * @return A pointer to an array of Position structures, each representing the (x, y) coordinates
 *         of a block of the piece relative to the piece's origin.
 */
Position* getTetrominoByPieceTypeAndRotation(PieceType type, Rotation rotation);
