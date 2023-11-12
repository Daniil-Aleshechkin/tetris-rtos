#include "BOARD_STATE_H.h"
#include "queue.h"

#ifndef TETRIS_GAME_STATE
#define TETRIS_GAME_STATE

struct CurrentPiece {
    Position location;
    Rotation rotation;
    PieceType type;
};

struct HoldPiece
{
    bool hasHeld;
    PieceType type;
};


struct TetrisGameState {
    PieceType** board;
    CurrentPiece* piece;
    HoldPiece* holdPiece;
    Queue* queue;
};

TetrisGameState* getDefaultTetrisGameState();
int8_t getStartingXPosFromPieceType(PieceType PieceType);
void freeTetrisGameState(TetrisGameState* state);
#endif