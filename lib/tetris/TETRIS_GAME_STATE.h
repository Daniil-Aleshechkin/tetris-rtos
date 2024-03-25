/**
 * @file TETRIS_GAME_STATE.h
 * @brief Structures and functions for managing the state of a Tetris game.
 *
 * This header file defines the data structures that represent the state of a Tetris game,
 * including the game board, the current piece in play, the piece held in reserve, and the
 * queue of upcoming pieces. It also declares functions for initializing the game state,
 * determining the starting position for new pieces, and cleaning up game state resources.
 */

#ifndef TETRIS_GAME_STATE
#define TETRIS_GAME_STATE

#include "BOARD_STATE_H.h"
#include "tetris_queue.h"

/**
 * @struct CurrentPiece
 * @brief Represents the currently active Tetris piece.
 *
 * Holds information about the currently active piece, including its type, position on the board,
 * and its orientation (rotation).
 */
struct CurrentPiece {
    Position location; ///< The current position of the piece on the game board.
    Rotation rotation; ///< The current orientation of the piece.
    PieceType type;    ///< The type of the Tetris piece.
};

/**
 * @struct HoldPiece
 * @brief Represents the Tetris piece held in reserve.
 *
 * Holds information about the piece currently held by the player, if any. This feature allows
 * players to swap their current piece with the one in hold.
 */
struct HoldPiece {
    bool hasHeld;      ///< Indicates whether a piece has been held during the current turn.
    PieceType type;    ///< The type of the piece currently held in reserve.
};

/**
 * @struct TetrisGameState
 * @brief Represents the complete state of a Tetris game.
 *
 * Contains all components necessary to represent the current state of a Tetris game,
 * including the game board, the current piece, the hold piece, and the queue of upcoming pieces.
 */
struct TetrisGameState {
    PieceType** board;     ///< The current state of the game board.
    CurrentPiece* piece;   ///< The currently active piece.
    HoldPiece* holdPiece;  ///< The piece currently held in reserve.
    Queue* queue;          ///< The queue of upcoming pieces.
};

/**
 * @brief Initializes the default state for a Tetris game.
 *
 * Allocates and returns a pointer to a TetrisGameState structure initialized to the default
 * starting state of the game.
 * 
 * @return Pointer to the initialized TetrisGameState structure.
 */
TetrisGameState* getDefaultTetrisGameState();

/**
 * @brief Determines the starting X position for a new Tetris piece based on its type.
 *
 * Calculates the appropriate starting horizontal position on the game board for new pieces
 * of the specified type, ensuring they are centered at the top of the board.
 *
 * @param PieceType The type of the Tetris piece.
 * @return The starting X position for the piece.
 */
int8_t getStartingXPosFromPieceType(PieceType PieceType);

/**
 * @brief Frees the resources associated with a Tetris game state.
 *
 * Cleans up and releases the memory allocated for the Tetris game state, including the
 * game board, current piece, hold piece, and the queue.
 *
 * @param state Pointer to the TetrisGameState structure to be freed.
 */
void freeTetrisGameState(TetrisGameState* state);

#endif /* TETRIS_GAME_STATE */
