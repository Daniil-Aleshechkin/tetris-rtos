#include "queue.h"
#include <stdlib.h>

PieceType* generateBag() {
    PieceType availableTypes[7] = {PIECE_TYPE_I, PIECE_TYPE_J, PIECE_TYPE_L, PIECE_TYPE_O, PIECE_TYPE_S, PIECE_TYPE_T, PIECE_TYPE_Z};  

    PieceType* bag = (PieceType*)malloc(sizeof(PieceType) * 7);
    
    for (int i = 0; i < 7; i++) {
        bag[i] = availableTypes[i];
    }

    for (int i = 0; i < 7; i++) {
        int randomIndex = rand() % 7;
        PieceType tmp = bag[i];
        bag[i] = bag[randomIndex];
        bag[randomIndex] = tmp;
    }

    return bag;
}

PieceType* peekQueue(Queue* queue, int size) {
    if (queue->queueStart == nullptr) {return nullptr;}

    PieceType* peek = (PieceType*) malloc(size * sizeof(PieceType));
    QueueElement* curr = queue->queueStart;

    for (int i = 0; i < size; i++) {
        if (curr == nullptr) {
            // Queue has fewer than `size` nodes, return what we peeked
            return nullptr;
        }
        peek[i] = curr->data;
        curr = curr->next;
    }
    
    return peek;
}

PieceType popQueue(Queue* queue) {
    if (queue->size == 0) {return PIECE_TYPE_N;}
    PieceType next = queue->queueStart->data;
    
    QueueElement* temp = queue->queueStart;
    queue->queueStart = queue->queueStart->next;
    free(temp);

    if (queue->size == 1) {
        queue->queueEnd = nullptr;
    }
    
    queue->size--;
    return next;
}

Queue* allocateQueue(int size, const PieceType queueData[]) {
    QueueElement* head;
    QueueElement* curr;
    QueueElement* nextElem;

    head = (QueueElement*)malloc(sizeof(QueueElement));
    head->data = queueData[0];
    head->next = nullptr;

    curr = head;
    
    for (int i = 1; i < size; i++) {
        nextElem = (QueueElement*)malloc(sizeof(QueueElement));
        nextElem->data = queueData[i];
        nextElem->next = nullptr;
        curr->next = nextElem;

        curr = curr->next;
    }

    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->queueStart = head;
    queue->queueEnd = curr;
    queue->size = size;

    return queue;
}

Queue* allocateEmptyQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->queueEnd = nullptr;
    queue->queueStart = nullptr;
    queue->size = 0;
    return queue;
}

void freeQueue(Queue* queue) {
    for (int i = 0; i < queue->size; i++) {
        popQueue(queue);
    }
    free(queue);
}

void addBag(Queue* queue) {
    QueueElement* curr = queue->queueEnd;

    PieceType* bag = generateBag();

    for (int i = 0; i < 7; i++) {
        QueueElement* new_node = (QueueElement*) malloc(sizeof(QueueElement));
        new_node->data = bag[i];
        new_node->next = nullptr;

        if (curr == nullptr) {
            queue->queueStart = new_node;
            curr = new_node;
        } else {
            curr->next = new_node;
        }
        
        if (i == 0 && queue->size == 0) {
            queue->queueStart = curr;
        }
        
        curr = new_node;
    }

    queue->queueEnd = curr;
    queue->size += 7;
}