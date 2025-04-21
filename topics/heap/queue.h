#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Node structure for the queue's linked list
 */
typedef struct node_
{
    void *data;         // Generic pointer to store data
    struct node_ *next; // Pointer to the next node
} node_t;

/**
 * Search data structure that will be stored in the queue
 */
typedef struct search_
{
    int data;  // Data value
    int index; // Index associated with the data
} search_t;

/**
 * Queue structure that maintains pointers to the front and back nodes
 */
typedef struct queue_
{
    node_t *front; // Pointer to the front of the queue
    node_t *back;  // Pointer to the back of the queue
    size_t length; // Current number of elements in the queue
} queue_t;

/**
 * Creates a new empty queue
 * @return Pointer to the newly created queue, or NULL if creation failed
 */
queue_t *create_queue();

/**
 * Adds a search element to the back of the queue
 * @param queue Pointer to the queue
 * @param search Search element to enqueue
 * @return true if successful, false otherwise
 */
bool enqueue(queue_t *queue, search_t search);

/**
 * Gets the element at the front of the queue without removing it
 * @param queue Pointer to the queue
 * @param search Pointer to store the front element
 * @return true if successful, false otherwise
 */
bool front(queue_t *queue, search_t *search);

/**
 * Gets the element at the back of the queue without removing it
 * @param queue Pointer to the queue
 * @param search Pointer to store the back element
 * @return true if successful, false otherwise
 */
bool back(queue_t *queue, search_t *search);

/**
 * Checks if the queue is empty
 * @param queue Pointer to the queue
 * @return true if the queue is empty, false otherwise
 */
bool isEmpty(queue_t *queue);

/**
 * Removes the element from the front of the queue
 * @param queue Pointer to the queue
 * @return true if successful, false otherwise
 */
bool dequeue(queue_t *queue);

/**
 * Destroys the queue and frees all memory
 * @param queue Pointer to the queue
 * @return true if successful, false otherwise
 */
bool destroy_queue(queue_t *queue);

/**
 * Frees all memory associated with the queue
 * @param queue Pointer to the queue
 */
void free_queue(queue_t *queue);

#endif /* QUEUE_H */