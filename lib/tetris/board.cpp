#include "board.h"
#include <stdlib.h>
#include "TETROMINOS.h"

void clearLines(PieceType** board, int* lines, int amount) {
    int clearedSoFar = 0;
    bool clearLine;

    for (int i = BOARD_HEIGHT - 1; i >= amount; i--) {
        
        // Check if the line should be cleared
        clearLine = false;
        for (int n = 0; n < amount; n++) {
            if (lines[n] == i) {
                clearLine = true;
            }
        }

        if (clearLine) {
            clearedSoFar++;
            continue;
        }    

        // Copy the line to what it should be in the future
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i+clearedSoFar][j] = board[i][j];
        }    
    }
    
    // Clear top rows since those will always be new empty lines
    for (int i = 0; i < amount; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = PIECE_TYPE_N;
        }
    }
}

void freeBoard(PieceType** oldBoard) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        free(oldBoard[i]);
    }
    free(oldBoard);    
}

PieceType** allocateConstantBoard(const PieceType constBoard[BOARD_HEIGHT][BOARD_WIDTH]) {
    PieceType** newBoard = (PieceType**)malloc(sizeof(PieceType*) * BOARD_HEIGHT);

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        newBoard[i] = (PieceType*)malloc(sizeof(PieceType*) * BOARD_WIDTH);
    
        for (int j = 0; j < BOARD_WIDTH; j++) {
            newBoard[i][j] = constBoard[i][j];
        }


    }

    return newBoard;
}



void placePiece(PieceType** board, PieceType type, Rotation rotation, Position position) {
    Position* minoLocations = getTetrominoByPieceTypeAndRotation(type, rotation);
    for (int i = 0; i < 4; ++i) {
        int boardX = minoLocations[i].xpos + position.xpos;
        int boardY = minoLocations[i].ypos + position.ypos;
        board[boardY][boardX] = type;
    }

    int* linesToClear = (int*)malloc(sizeof(int)*4);
    int amount = 0;
    bool clearLine;
    for (int i = 0; i< BOARD_HEIGHT; i++) {
        clearLine = true;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] == PIECE_TYPE_N) {
                clearLine = false;
            }
        }

        if (clearLine) {
            linesToClear[amount] = i;
            amount++;
        }
    }

    clearLines(board, linesToClear, amount);
    free(linesToClear);
}

bool validatePlacement(PieceType** board, PieceType type, Rotation rotation, Position position) {
    Position* minoLocations = getTetrominoByPieceTypeAndRotation(type, rotation);
    for (int i = 0; i < 4; ++i) {
        int boardX = minoLocations[i].xpos + position.xpos;
        int boardY = minoLocations[i].ypos + position.ypos;
        if (boardX < 0 || boardX >= BOARD_WIDTH || boardY < 0 || boardY >= BOARD_HEIGHT || board[boardY][boardX] != PIECE_TYPE_N) {
            return false;
        }
    }

    return true;
}

PieceType** allocateDefaultBoard() {
    PieceType** board = (PieceType**)malloc(sizeof(PieceType*) * BOARD_HEIGHT);

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        board[i] = (PieceType*)malloc(sizeof(PieceType*) * BOARD_WIDTH);
    
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = DEFAULT_BOARD_STATE[i][j];
        }
    }

    return board;
}