#include "TETRIS_GAME_STATE.h"
#include <stdlib.h>
#include "queue.h"
#include "board.h"
int8_t getStartingXPosFromPieceType(PieceType pieceType) {
    switch (pieceType)
    {
    case PIECE_TYPE_I:
    case PIECE_TYPE_J:
    case PIECE_TYPE_Z:
    case PIECE_TYPE_T:
    case PIECE_TYPE_L:
    case PIECE_TYPE_S:
        return 3;
    case PIECE_TYPE_O:
        return 4;
    default:
        return 0;
    }
}

TetrisGameState* getDefaultTetrisGameState() {
    TetrisGameState* gameState = (TetrisGameState*)malloc(sizeof(TetrisGameState));

    HoldPiece* holdPiece = (HoldPiece*)malloc(sizeof(HoldPiece));
    holdPiece->hasHeld = false;
    holdPiece->type = PIECE_TYPE_N;

    Queue* queue = allocateEmptyQueue();
    addBag(queue);
    addBag(queue);

    PieceType currentPieceType = popQueue(queue);

    CurrentPiece* currentPiece = (CurrentPiece*)malloc(sizeof(CurrentPiece));
    currentPiece->location = {getStartingXPosFromPieceType(currentPieceType), 0};
    currentPiece->rotation = DEG_0;
    currentPiece->type = currentPieceType;

    gameState->queue = queue;
    gameState->holdPiece = holdPiece;
    gameState->board = allocateDefaultBoard();
    gameState->piece = currentPiece;

    return gameState;
}

void freeTetrisGameState(TetrisGameState* state) {
    freeQueue(state->queue);
    freeBoard(state->board);
    free(state->holdPiece);
    free(state->piece);

    free(state);
}