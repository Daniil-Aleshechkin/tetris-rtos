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

TetrisGameState* rotatePiece(TetrisGameState* state, Rotation rotation );
TetrisGameState* softDropPiece(TetrisGameState* state);
TetrisGameState* hardDropPiece(TetrisGameState* state);
TetrisGameState* movePiece(TetrisGameState* state, bool isLeft);
TetrisGameState* reset(TetrisGameState* state);

char** printState(TetrisGameState* state);
void freePrintedBytes(char** printedState);
char getCharFromPieceType(PieceType pieceType);

#endif