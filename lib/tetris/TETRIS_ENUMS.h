#include <stdint.h>

#ifndef TETRIS_ENUMS
#define TETRIS_ENUMS

typedef enum {
    PIECE_TYPE_N,
    PIECE_TYPE_I,
    PIECE_TYPE_J,
    PIECE_TYPE_L,
    PIECE_TYPE_O,
    PIECE_TYPE_S,
    PIECE_TYPE_T,
    PIECE_TYPE_Z
} PieceType;

typedef enum {
    DEG_0,
    DEG_90,
    DEG_180,
    DEG_270
} Rotation;

typedef struct {
    int8_t xpos;
    int8_t ypos;
} Position;

#endif