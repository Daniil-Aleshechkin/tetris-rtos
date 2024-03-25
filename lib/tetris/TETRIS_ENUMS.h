/**
 * @file TETRIS_ENUMS.h
 * @brief Enumerations and structures defining Tetris piece types, rotation states, and positions.
 *
 * This header file contains definitions crucial for representing the state and behavior of Tetris pieces within the game.
 * It includes the PieceType enumeration for identifying different Tetris pieces, the Rotation enumeration for managing piece
 * orientations, and the Position structure for specifying locations on the game board.
 */

#include <stdint.h>

#ifndef TETRIS_ENUMS
#define TETRIS_ENUMS

/**
 * @enum PieceType
 * @brief Enumerates the types of Tetris pieces.
 *
 * Defines identifiers for each Tetris piece type, including the special PIECE_TYPE_N used to denote empty cells or no piece.
 */
typedef enum {
    PIECE_TYPE_N, ///< Represents no piece or an empty cell.
    PIECE_TYPE_I, ///< The "I" Tetris piece.
    PIECE_TYPE_J, ///< The "J" Tetris piece.
    PIECE_TYPE_L, ///< The "L" Tetris piece.
    PIECE_TYPE_O, ///< The "O" Tetris piece.
    PIECE_TYPE_S, ///< The "S" Tetris piece.
    PIECE_TYPE_T, ///< The "T" Tetris piece.
    PIECE_TYPE_Z  ///< The "Z" Tetris piece.
} PieceType;


/**
 * @enum Rotation
 * @brief Enumerates the rotation states of Tetris pieces.
 *
 * Defines the possible orientations (rotation states) of a Tetris piece. The rotations are increments of 90 degrees.
 */
typedef enum {
    DEG_0,   ///< 0 degrees rotation (default orientation).
    DEG_90,  ///< 90 degrees clockwise rotation.
    DEG_180, ///< 180 degrees rotation.
    DEG_270  ///< 270 degrees clockwise rotation (or 90 degrees counterclockwise).
} Rotation;

/**
 * @struct Position
 * @brief Represents a position on the Tetris game board.
 *
 * Defines a structure for specifying the (x, y) coordinates of a piece or cell on the game board.
 */
typedef struct {
    int8_t xpos; ///< The x-coordinate (horizontal position) on the game board.
    int8_t ypos; ///< The y-coordinate (vertical position) on the game board.
} Position;

#endif