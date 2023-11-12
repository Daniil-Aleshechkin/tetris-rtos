#include "BOARD_STATE_H.h"

#ifndef BOARD
#define BOARD

void placePiece(PieceType** board , PieceType type, Rotation rotation, Position position);

bool validatePlacement(PieceType** board , PieceType type, Rotation rotation, Position position);

PieceType** allocateDefaultBoard();
void freeBoard(PieceType** board);
PieceType** allocateConstantBoard(const PieceType constBoard[BOARD_HEIGHT][BOARD_WIDTH]);

#endif