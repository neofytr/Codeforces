#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "dynarr.h"
#include <stdbool.h>

// Max heap is implemented using a dynamic array
typedef dyn_arr_t max_heap_t;

// Forward declaration of binary tree type
typedef struct binary_tree binary_tree_t;

/**
 * Creates a new max heap data structure
 *
 * @return A pointer to the newly created max heap, or NULL if creation failed
 */
max_heap_t *max_heap_create();

/**
 * Inserts an element into the max heap
 *
 * @param max_heap Pointer to the max heap
 * @param element The integer element to insert
 * @return true if successful, false if insertion failed
 */
bool max_heap_insert(max_heap_t *max_heap, int element);

/**
 * Deletes the maximum element from the max heap
 *
 * @param max_heap Pointer to the max heap
 * @param element Pointer to store the deleted element
 * @return true if successful, false if deletion failed
 */
bool max_heap_delete(max_heap_t *max_heap, int *element);

/**
 * Sorts the elements in the max heap
 *
 * @param max_heap Pointer to the max heap
 * @return A sorted dynamic array containing the elements, or NULL if sorting failed
 */
dyn_arr_t *heap_sort(max_heap_t *max_heap);

/**
 * Converts a binary tree to a max heap
 *
 * @param binary_tree Pointer to the binary tree
 * @return A pointer to the max heap, or NULL if conversion failed
 */
max_heap_t *conv_to_max_heap(binary_tree_t *binary_tree);

/**
 * Frees all memory associated with a max heap
 *
 * @param max_heap Pointer to the max heap
 */
void max_heap_free(max_heap_t *max_heap);

#endif // MAX_HEAP_H