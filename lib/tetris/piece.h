/**
 * @file piece.h
 * @brief Functions for Tetris piece operations and game state management.
 *
 * This header file provides declarations for functions involved in rotating, moving,
 * dropping Tetris pieces, and managing the Tetris game state. It includes utilities
 * for printing the game state to a terminal or a specific display and for resetting
 * the game state.
 */

#include "TETRIS_ENUMS.h"
#include "board.h"
#include "TETRIS_GAME_STATE.h"

#ifndef PIECE
#define PIECE

#define HOLDPIECEWIDTH 5
#define QUEUEWIDTH 5
#define LONG_BOARD_WIDTH (HOLDPIECEWIDTH + BOARD_WIDTH + QUEUEWIDTH + 2)
#define SHORT_BOARD_WIDTH (HOLDPIECEWIDTH + BOARD_WIDTH + 2)

#define QUEUEHEIGHT 14

/**
 * @brief Rotate the current piece in the game state.
 * 
 * @param state Pointer to the current game state.
 * @param rotation The rotation direction (DEG_0, DEG_90, DEG_180, DEG_270).
 * @return Pointer to the updated game state after rotation.
 */
TetrisGameState* rotatePiece(TetrisGameState* state, Rotation rotation);

/**
 * @brief Soft drop the current piece.
 * 
 * Moves the current piece down until it hits an obstacle.
 * 
 * @param state Pointer to the current game state.
 * @return Pointer to the updated game state after soft dropping the piece.
 */
TetrisGameState* softDropPiece(TetrisGameState* state);

/**
 * @brief Hard drop the current piece.
 * 
 * Instantly moves the current piece to its lowest possible position.
 * 
 * @param state Pointer to the current game state.
 * @return Pointer to the updated game state after hard dropping the piece.
 */
TetrisGameState* hardDropPiece(TetrisGameState* state);

/**
 * @brief Move the current piece left or right.
 * 
 * @param state Pointer to the current game state.
 * @param isLeft Boolean indicating the direction of movement (true for left, false for right).
 * @return Pointer to the updated game state after moving the piece.
 */
TetrisGameState* movePiece(TetrisGameState* state, bool isLeft);

/**
 * @brief Reset the game state to its default configuration.
 * 
 * @param state Pointer to the current game state.
 * @return Pointer to the reset game state.
 */
TetrisGameState* reset(TetrisGameState* state);

/**
 * @brief Print the current game state to a string array.
 * 
 * @param state Pointer to the current game state.
 * @return 2D array of chars representing the printed state.
 */
char** printState(TetrisGameState* state);

/**
 * @brief Free the memory allocated for the printed state.
 * 
 * @param printedState 2D array of chars representing the printed state.
 */
void freePrintedBytes(char** printedState);

/**
 * @brief Get the character representation of a Tetris piece type.
 * 
 * @param pieceType The Tetris piece type.
 * @return Character representing the piece type.
 */
char getCharFromPieceType(PieceType pieceType);

/**
 * @brief Display the current game state on the WS2821 LED display.
 * 
 * @param state Pointer to the current game state.
 */
void displayState(TetrisGameState* state);

#endif