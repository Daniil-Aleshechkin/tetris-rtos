#include "srs.h"

SRSOffest* getISRSOffsets(Rotation currentRotation, Rotation rotation);

SRSOffest* getSRSOffsetsFromTypeAndRotation(PieceType type, Rotation currentRotation , Rotation rotation, int* offsetAmount) {
    if (rotation == DEG_180) {
        *offsetAmount = 5;
        return (SRSOffest*)offsets180[currentRotation];
    }
    
    if (type == PIECE_TYPE_I) {
        *offsetAmount = 6;
        return getISRSOffsets(currentRotation, rotation);
    }

    *offsetAmount = 5;
    
    if (rotation == DEG_90) {
        return (SRSOffest*)offsets90[currentRotation];
    } else {
        return (SRSOffest*)offsets270[currentRotation];
    }
}

SRSOffest* getISRSOffsets(Rotation currentRotation, Rotation rotation) {
    if (rotation = DEG_90) {
        return (SRSOffest*)offsetsI90[currentRotation];
    } else {
        return (SRSOffest*)offsets90[currentRotation];
    }
}