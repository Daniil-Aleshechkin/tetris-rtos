#include "TETRIS_ENUMS.h"

#ifndef QUEUE
#define QUEUE

struct QueueElement {
    QueueElement* next;
    PieceType data;
};

struct Queue {
    QueueElement* queueStart;
    QueueElement* queueEnd;
    int size;
};

void addBag(Queue* queue);
PieceType popQueue(Queue* queue);
PieceType* peekQueue(Queue* queue, int size);
PieceType* generateBag();
Queue* allocateQueue(int size, const PieceType queueData[]);
Queue* allocateEmptyQueue();

void freeQueue(Queue* queue);
#endif