#include "piece.h"
#include "board.h"
#include "TETRIS_GAME_STATE.h"
#include "TETROMINOS.h"
#include <stdlib.h>
#include <stdio.h>
#include "srs.h"
#include "com_14646_matrix.h"

TetrisGameState* rotatePiece(TetrisGameState *state, Rotation rotation)
{
    if (rotation == DEG_0) {
        return state;
    }

    Rotation newRotation = (Rotation)((state->piece->rotation + rotation) % 4);
    Position newPosition;

    int* offsetAmount = (int*)malloc(sizeof(int));
    SRSOffest* srsOffets = getSRSOffsetsFromTypeAndRotation(state->piece->type, state->piece->rotation, rotation, offsetAmount);

    for (int i = 0; i < *offsetAmount; i++) {
        newPosition.xpos = state->piece->location.xpos + srsOffets[i].offsetx;
        newPosition.ypos = state->piece->location.ypos + srsOffets[i].offsety;

        if (validatePlacement(state->board, state->piece->type, newRotation, newPosition)) {
            state->piece->rotation = newRotation;
            state->piece->location.xpos = newPosition.xpos;
            state->piece->location.ypos = newPosition.ypos;
            break;
        }    
    }

    return state;
}

void softDropPosition(TetrisGameState* state, Position* newPosition) {
    while (validatePlacement(state->board, state->piece->type, state->piece->rotation, *newPosition)) {
        newPosition->ypos++;
    }

    newPosition->ypos--;
}

TetrisGameState* softDropPiece(TetrisGameState *state) {
    Position* newPosition = (Position*)malloc(sizeof(Position));
    newPosition->xpos = state->piece->location.xpos;
    newPosition->ypos = state->piece->location.ypos;

    softDropPosition(state, newPosition);

    state->piece->location = *newPosition;
    free(newPosition);

    return state;
}

bool isPlacementAbove(TetrisGameState* state) {
    Position* positions = getTetrominoByPieceTypeAndRotation(state->piece->type, state->piece->rotation);

    for (int i = 0; i < 4; i++) {
        if (positions[i].ypos+state->piece->location.ypos >= 3) {
            return false;
        }
    }

    return true;
}

TetrisGameState* hardDropPiece(TetrisGameState *state) {
    state = softDropPiece(state);
    
    if (isPlacementAbove(state)) {
        return reset(state);
    }

    placePiece(state->board, state->piece->type, state->piece->rotation, state->piece->location);

    PieceType nextPiece = popQueue(state->queue);
    Position nextPosition = {getStartingXPosFromPieceType(nextPiece), 0};

    if (state->queue->size < 14) {
        addBag(state->queue);
    }

    if (nextPiece != PIECE_TYPE_N && !validatePlacement(state->board, nextPiece, DEG_0, nextPosition)) {
        return reset(state);
    }

    state->piece->location = nextPosition;
    state->piece->rotation = DEG_0;
    state->piece->type = nextPiece;
    state->holdPiece->hasHeld = false;


    return state;
}

TetrisGameState* reset(TetrisGameState* state) {
    freeTetrisGameState(state);
    return (TetrisGameState*)getDefaultTetrisGameState();
}

TetrisGameState* movePiece(TetrisGameState *state, bool isLeft) {
    Position* newPosition = (Position*)malloc(sizeof(Position));
    newPosition->xpos = state->piece->location.xpos;
    newPosition->ypos = state->piece->location.ypos;
    
    if (isLeft) {
        newPosition->xpos--;
    } else {
        newPosition->xpos++;
    }

    if (validatePlacement(state->board, state->piece->type, state->piece->rotation, *newPosition)) {
        state->piece->location = *newPosition;
    }

    free(newPosition);

    return state;
}

char getCharFromPieceType(PieceType pieceType) {
    switch (pieceType)
    {
    case PIECE_TYPE_I:
        return 'I';
    case PIECE_TYPE_J:
        return 'J';
    case PIECE_TYPE_L:
        return 'L';
    case PIECE_TYPE_O:
        return 'O';
    case PIECE_TYPE_S:
        return 'S';
    case PIECE_TYPE_T:
        return 'T';
    case PIECE_TYPE_Z:
        return 'Z';
    default:
        return '.';
    }
}

void printBoard(PieceType** board, char** printedState) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] == PIECE_TYPE_N && i > 2) {
                printedState[i][HOLDPIECEWIDTH+j] = '.';
                continue;
            } else if (board[i][j] == PIECE_TYPE_N && i < 3) {
                continue;
            }
            printedState[i][HOLDPIECEWIDTH+j] = getCharFromPieceType(board[i][j]);
        }
    }
}

void freePrintedBytes(char** bytes) {
    for (int i = 0; i < 23; i++) {
        free(bytes[i]);
    }

    free(bytes);
}

void printQueue(Queue* queue, char** printedState) {
    PieceType* nextPieces = peekQueue(queue, 5);
    
    for (int i = 0; i < 5; i++) {
        if (nextPieces[i] == PIECE_TYPE_N) {continue;}

        for (int j = 0; j < 4; j++) {
            Position* positions = getTetrominoByPieceTypeAndRotation(nextPieces[i], DEG_0);
            printedState[3*i+positions[j].ypos][BOARD_WIDTH+HOLDPIECEWIDTH+positions[j].xpos+1] = getCharFromPieceType(nextPieces[i]);
        }   
    }

    free(nextPieces);
}

void printHoldPiece(HoldPiece* holdPiece, char** printedState) {
    if (holdPiece->type == PIECE_TYPE_N) {return;}
    Position* holdPiecePositions = getTetrominoByPieceTypeAndRotation(holdPiece->type, DEG_0);
    
    for (int i = 0; i < 4; i++) {
        printedState[holdPiecePositions[i].ypos][holdPiecePositions[i].xpos] = getCharFromPieceType(holdPiece->type);
    }
}

void printCurrentPiece(CurrentPiece* curPiece, char** printedState) {
    Position* curPiecePositions = getTetrominoByPieceTypeAndRotation(curPiece->type, curPiece->rotation);

    for (int i = 0; i < 4; i++) {
        printedState[curPiece->location.ypos + curPiecePositions[i].ypos][HOLDPIECEWIDTH + curPiece->location.xpos + curPiecePositions[i].xpos] = getCharFromPieceType(curPiece->type);
    }
}

void printGhostPiece(TetrisGameState* state, char** printedState) {
    Position* curPiecePositions = getTetrominoByPieceTypeAndRotation(state->piece->type, state->piece->rotation);

    Position* ghostPiecePos = (Position*)malloc(sizeof(Position));
    ghostPiecePos->xpos = state->piece->location.xpos;
    ghostPiecePos->ypos = state->piece->location.ypos;

    softDropPosition(state, ghostPiecePos);

    for (int i = 0; i< 4; i++) { 
        printedState[ghostPiecePos->ypos + curPiecePositions[i].ypos][HOLDPIECEWIDTH + ghostPiecePos->xpos + curPiecePositions[i].xpos] = 'X';
    }

    free(ghostPiecePos);
}

char** printState(TetrisGameState* state) {
    char** printedState = (char**)malloc(sizeof(char*)*BOARD_HEIGHT);

    for(int i = 0; i < QUEUEHEIGHT; i++) {
        printedState[i] = (char*)malloc(sizeof(char) * LONG_BOARD_WIDTH);
        
        for (int j = 0; j < LONG_BOARD_WIDTH - 2; j++) {
            printedState[i][j] = ' ';
        }

        printedState[i][LONG_BOARD_WIDTH - 2] = '\n';
        printedState[i][LONG_BOARD_WIDTH - 1] = 0x0;
    }

    for (int i = QUEUEHEIGHT; i < BOARD_HEIGHT; i++) {
        printedState[i] = (char*)malloc(sizeof(char) * SHORT_BOARD_WIDTH);
        
        for (int j = 0; j < SHORT_BOARD_WIDTH - 2; j++) {
            printedState[i][j] = ' ';
        }

        printedState[i][SHORT_BOARD_WIDTH - 2] = '\n';
        printedState[i][SHORT_BOARD_WIDTH - 1] = 0x0;
    }

    printBoard(state->board, printedState);
    printGhostPiece(state, printedState);
    printCurrentPiece(state->piece, printedState);

    printHoldPiece(state->holdPiece, printedState);
    printQueue(state->queue, printedState);

    return printedState;
    
}

static pixel I_COLOR = {false, true, true};
static pixel O_COLOR = {true, true, false};
static pixel T_COLOR = {true, false, true};
static pixel S_COLOR = {false, true, false};
static pixel Z_COLOR = {true, false, false};
static pixel J_COLOR = {false, false, true};
static pixel L_COLOR = {true, true, false};
static pixel SHADOW_COLOR = {true, true, true};
static pixel NO_COLOR = {false, false, false};

struct pixel getPieceColor(PieceType type) {
    switch (type)
    {
    case PIECE_TYPE_I:
        return I_COLOR;
    case PIECE_TYPE_J:
        return J_COLOR;
    case PIECE_TYPE_O:
        return O_COLOR;
    case PIECE_TYPE_Z:
        return Z_COLOR;
    case PIECE_TYPE_T:
        return T_COLOR;
    case PIECE_TYPE_S:
        return S_COLOR;
    case PIECE_TYPE_L:
        return L_COLOR;
    default:
        return NO_COLOR;    
    }

}

void drawPiece(PieceType type, Rotation rotation, Position position) {
    if (type == PieceType::PIECE_TYPE_N) {return;}

    Position* piecePositions = getTetrominoByPieceTypeAndRotation(type, rotation);
    
    for (int i = 0; i < 4; i++) {
        int xPos = piecePositions[i].xpos + position.xpos;
        int yPos = position.ypos - piecePositions[i].ypos;

        bufferPixel(getPieceColor(type), xPos, yPos);
    }
}

void drawGhostPiece(PieceType type, Rotation rotation, Position position) {
    if (type == PieceType::PIECE_TYPE_N) {return;}

    Position* piecePositions = getTetrominoByPieceTypeAndRotation(type, rotation);
    
    for (int i = 0; i < 4; i++) {
        int xPos = piecePositions[i].xpos + position.xpos;
        int yPos = position.ypos - piecePositions[i].ypos;

        bufferPixel(SHADOW_COLOR, xPos, yPos);
    }
}


void displayState(TetrisGameState* state) {
    clearBuffer();

    // frame
    for (int y = 0; y < 24; y++) {
        bufferPixel(SHADOW_COLOR, 10, y);
    }

    for (int y = 0; y < 24; y++) {
        bufferPixel(SHADOW_COLOR, 21, y);
    }


    // hold piece
    drawPiece(state->holdPiece->type, Rotation::DEG_0, {6, 20});

    // queue 
    drawPiece(state->queue->queueStart->data, Rotation::DEG_0, {22, 20});
    drawPiece(state->queue->queueStart->next->data, Rotation::DEG_0, {22, 17});
    drawPiece(state->queue->queueStart->next->next->data, Rotation::DEG_0, {22, 14});
    drawPiece(state->queue->queueStart->next->next->next->data, Rotation::DEG_0, {22, 11});
    drawPiece(state->queue->queueStart->next->next->next->next->data, Rotation::DEG_0, {22, 8});

    // board (only the middle 4x8 for now)

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            bufferPixel(getPieceColor(state->board[y][x]), x+11, BOARD_HEIGHT-y-1);
        }
    }

    // ghost piece
    Position ghostPiecePos;
    ghostPiecePos.xpos = state->piece->location.xpos;
    ghostPiecePos.ypos = state->piece->location.ypos;

    softDropPosition(state, &ghostPiecePos); 
    
    ghostPiecePos.xpos += 11;
    ghostPiecePos.ypos = BOARD_HEIGHT - ghostPiecePos.ypos -1;

    drawGhostPiece(state->piece->type, state->piece->rotation, ghostPiecePos);

    // piece
    Position curPiecePosition;

    curPiecePosition.xpos = state->piece->location.xpos + 11;
    curPiecePosition.ypos = BOARD_HEIGHT - state->piece->location.ypos - 1;

    drawPiece(state->piece->type, state->piece->rotation, curPiecePosition);
}
