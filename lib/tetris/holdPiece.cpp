#include "holdPiece.h"
#include <stdlib.h>

void holdPiece(HoldPiece* holdPiece, Queue* queue, CurrentPiece* currentPiece) {
    if (holdPiece->hasHeld) { return;}

    holdPiece->hasHeld = true; 

    if (holdPiece->type == PIECE_TYPE_N) {
        if (queue == nullptr || queue->size == 0) {return;}
        holdPiece->type = currentPiece->type;
        currentPiece->type = popQueue(queue);
        
    } else {
        PieceType newType = currentPiece->type;
        currentPiece->type = holdPiece->type;
        holdPiece->type = newType;
    }
}