#include "TETROMINOS.h"
#include "PIECE_STATE_I.h"
#include "PIECE_STATE_O.h"
#include "PIECE_STATE_J.h"
#include "PIECE_STATE_L.h"
#include "PIECE_STATE_S.h"
#include "PIECE_STATE_T.h"
#include "PIECE_STATE_Z.h"

Position* getTetrominoByPieceTypeAndRotation(PieceType pieceType, Rotation rotation) {
    switch (pieceType) {
        case PIECE_TYPE_I: return getIPieceByRotation(rotation);
        case PIECE_TYPE_J: return getJPieceByRotation(rotation);
        case PIECE_TYPE_L: return getLPieceByRotation(rotation);
        case PIECE_TYPE_S: return getSPieceByRotation(rotation);
        case PIECE_TYPE_T: return getTPieceByRotation(rotation);
        case PIECE_TYPE_Z: return getZPieceByRotation(rotation);
        case PIECE_TYPE_O: return (Position*)PIECE_O;
        default: return nullptr;
    }
}
Position* getIPieceByRotation(Rotation rotation) {
    switch (rotation) {
        case DEG_0:
            return (Position*)PIECE_I_0;
        case DEG_90:
            return (Position*)PIECE_I_90;
        case DEG_180:
            return (Position*)PIECE_I_180;
        case DEG_270:
            return (Position*)PIECE_I_270;
        default: return nullptr;
    }
}

Position* getJPieceByRotation(Rotation rotation) {
    switch (rotation) {
        case DEG_0:
            return (Position*)PIECE_J_0;
        case DEG_90:
            return (Position*)PIECE_J_90;
        case DEG_180:
            return (Position*)PIECE_J_180;
        case DEG_270:
            return (Position*)PIECE_J_270;
        default: return nullptr;
    }
}

Position* getLPieceByRotation(Rotation rotation) {
    switch (rotation) {
        case DEG_0:
            return (Position*)PIECE_L_0;
        case DEG_90:
            return (Position*)PIECE_L_90;
        case DEG_180:
            return (Position*)PIECE_L_180;
        case DEG_270:
            return (Position*)PIECE_L_270;
        default:
            return nullptr;
    }
}

Position* getZPieceByRotation(Rotation rotation) {
    switch (rotation) {
        case DEG_0:
            return (Position*)PIECE_Z_0;
        case DEG_90:
            return (Position*)PIECE_Z_90;
        case DEG_180:
            return (Position*)PIECE_Z_180;
        case DEG_270:
            return (Position*)PIECE_Z_270;
        default: return nullptr;
    }
}

Position* getTPieceByRotation(Rotation rotation) {
    switch (rotation) {
        case DEG_0:
            return (Position*)PIECE_T_0;
        case DEG_90:
            return (Position*)PIECE_T_90;
        case DEG_180:
            return (Position*)PIECE_T_180;
        case DEG_270:
            return (Position*)PIECE_T_270;
        default: return nullptr;
    }
}

Position* getSPieceByRotation(Rotation rotation) {
    switch (rotation) {
        case DEG_0:
            return (Position*)PIECE_S_0;
        case DEG_90:
            return (Position*)PIECE_S_90;
        case DEG_180:
            return (Position*)PIECE_S_180;
        case DEG_270:
            return (Position*)PIECE_S_270;
        default: return nullptr;
    }
}