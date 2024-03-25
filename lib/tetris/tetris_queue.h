/**
 * @file tetris_queue.h
 * @brief Functions and structures for managing the Tetris piece queue.
 *
 * This header file provides the definitions for managing a queue of Tetris pieces, 
 * including generating a bag of pieces, adding it to the queue, and retrieving pieces from the queue. 
 * The queue is used to determine the order in which Tetris pieces appear during gameplay.
 */

#ifndef TETRIS_QUEUE
#define TETRIS_QUEUE

#include "TETRIS_ENUMS.h"

/**
 * @struct QueueElement
 * @brief Represents an element in the queue.
 * 
 * This structure is a node in the queue that holds a Tetris piece and a pointer to the next element.
 */
struct QueueElement {
    QueueElement* next; ///< Pointer to the next element in the queue.
    PieceType data;     ///< The Tetris piece type held by this element.
};

/**
 * @struct Queue
 * @brief Represents the queue of Tetris pieces.
 * 
 * This structure defines the queue used to manage the upcoming Tetris pieces during gameplay.
 */
struct Queue {
    QueueElement* queueStart; ///< Pointer to the start of the queue.
    QueueElement* queueEnd;   ///< Pointer to the end of the queue.
    int size;                 ///< The current size of the queue.
};

/**
 * @brief Adds a randomized bag of Tetris pieces to the queue.
 * 
 * @param queue Pointer to the Queue structure to which the bag will be added.
 */
void addBag(Queue* queue);

/**
 * @brief Removes and returns the first Tetris piece from the queue.
 * 
 * @param queue Pointer to the Queue structure from which the piece will be popped.
 * @return The Tetris piece type that was at the start of the queue.
 */
PieceType popQueue(Queue* queue);

/**
 * @brief Peeks at the first few pieces in the queue without removing them.
 * 
 * @param queue Pointer to the Queue structure to be peeked.
 * @param size The number of pieces to peek at.
 * @return An array of Tetris piece types at the start of the queue.
 */
PieceType* peekQueue(Queue* queue, int size);

/**
 * @brief Generates a randomized bag of all seven Tetris piece types.
 * 
 * @return A pointer to an array of randomized Tetris piece types.
 */
PieceType* generateBag();

/**
 * @brief Allocates and initializes a queue with the specified Tetris pieces.
 * 
 * @param size The number of pieces to include in the new queue.
 * @param queueData Array of Tetris piece types to initialize the queue.
 * @return Pointer to the newly allocated Queue structure.
 */
Queue* allocateQueue(int size, const PieceType queueData[]);

/**
 * @brief Allocates and initializes an empty queue.
 * 
 * @return Pointer to the newly allocated, empty Queue structure.
 */
Queue* allocateEmptyQueue();

/**
 * @brief Frees the resources associated with a Tetris piece queue.
 * 
 * @param queue Pointer to the Queue structure to be freed.
 */
void freeQueue(Queue* queue);

#endif /* TETRIS_QUEUE */
