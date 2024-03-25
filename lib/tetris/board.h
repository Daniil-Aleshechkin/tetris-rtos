/**
 * @file board.h
 * @brief Functions for managing the Tetris game board.
 *
 * This header file defines functions for manipulating the Tetris game board,
 * including placing pieces, validating piece placements, clearing lines, and
 * managing the memory of the board.
 */

#include "BOARD_STATE_H.h"

#ifndef BOARD
#define BOARD

/**
 * @brief Places a piece on the board and clears any completed lines.
 *
 * This function places a piece on the board based on the specified type,
 * rotation, and position. It automatically checks for and clears any completed
 * lines after placing the piece.
 *
 * @param board The current game board.
 * @param type The type of the piece to place.
 * @param rotation The rotation state of the piece.
 * @param position The position on the board where the piece is to be placed.
 */
void placePiece(PieceType** board , PieceType type, Rotation rotation, Position position);

/**
 * @brief Validates whether a piece can be placed on the board.
 *
 * Checks if a piece can be placed at the specified location on the board without
 * colliding with existing pieces or exceeding the board boundaries.
 *
 * @param board The current game board.
 * @param type The type of the piece to validate.
 * @param rotation The rotation state of the piece.
 * @param position The position on the board to check for validity.
 * @return true if the piece can be placed at the specified location, false otherwise.
 */
bool validatePlacement(PieceType** board , PieceType type, Rotation rotation, Position position);

/**
 * @brief Allocates and initializes a default game board.
 *
 * Allocates memory for a new game board and initializes it with a default state.
 *
 * @return A pointer to the newly allocated and initialized game board.
 */
PieceType** allocateDefaultBoard();

/**
 * @brief Frees the memory allocated for a game board.
 *
 * Frees the memory used by a game board and all its elements.
 *
 * @param board The game board to free.
 */
void freeBoard(PieceType** board);

/**
 * @brief Allocates and initializes a game board with a constant state.
 *
 * Allocates memory for a new game board and initializes it with the state provided
 * by the constBoard parameter.
 *
 * @param constBoard A 2D array defining the state to initialize the board with.
 * @return A pointer to the newly allocated and initialized game board.
 */
PieceType** allocateConstantBoard(const PieceType constBoard[BOARD_HEIGHT][BOARD_WIDTH]);

#endif