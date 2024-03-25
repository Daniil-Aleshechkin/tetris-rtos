/**
 * @file holdPiece.h
 * @brief Interface for holding a Tetris piece.
 *
 * Provides functionality to hold a Tetris piece for later use. This file
 * includes the declaration of the function used to swap the current active
 * piece with the one in hold, if any. It integrates with the game's state
 * management by accessing and modifying the current piece and the queue
 * of upcoming pieces.
 */

#include "TETRIS_GAME_STATE.h"

/**
 * @brief Holds or swaps the current Tetris piece.
 *
 * This function allows a player to hold the current piece or swap it with
 * an already held piece. It ensures that a piece can only be held once until
 * a new piece is spawned. If no piece is currently held, the function places
 * the current piece in hold and retrieves the next piece from the queue.
 *
 * @param holdPiece The current hold state, including whether a piece is held and its type.
 * @param queue The queue of upcoming pieces.
 * @param currentPiece The current active piece.
 *
 * @note This function modifies the holdPiece, queue, and currentPiece structures.
 */
void holdPiece(HoldPiece* hold, Queue* queue, CurrentPiece* piece);
