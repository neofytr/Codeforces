#include "max_heap.h"
#include "binary_tree.h"
#include <errno.h>
#include <stdio.h>

#define DEFAULT_SIZE 1024


/**
 * Creates a new max heap data structure
 *
 * @return A pointer to the newly created max heap, or NULL if creation failed
 */
max_heap_t *max_heap_create() {
    int default_val = -1; // signifies no element is there (sentinel value)
    dyn_arr_t *arr = dyn_arr_create(DEFAULT_SIZE, sizeof(int), &default_val);
    if (!arr) {
        fprintf(stderr, "ERROR: max heap creation failed: %s\n", strerror(errno));
        return NULL;
    }

    return arr;
}

/**
 * Inserts an element into the max heap
 *
 * This function maintains the max heap property by bubbling up the new element
 * to its correct position after insertion.
 *
 * @param max_heap Pointer to the max heap
 * @param element The integer element to insert
 * @return true if successful, false if insertion failed
 */
bool max_heap_insert(max_heap_t *max_heap, int element) {
    if (!max_heap) {
        fprintf(stderr, "ERROR: invalid max heap argument\n");
        return false;
    }

    // insert element at the end and bubble up
    if (!dyn_arr_append(max_heap, &element)) // inserting at the end doesn't make the binary tree incomplete
    {
        fprintf(stderr, "ERROR: failed to append element to max heap\n");
        return false;
    }

    size_t new_element_index = max_heap->last_index;
    if (!new_element_index) {
        // The element is now the root, no need to bubble up
        return true;
    }

    int parent;
    size_t parent_index = (new_element_index - 1) / 2;

    // Get the parent element
    if (!dyn_arr_get(max_heap, parent_index, &parent)) {
        fprintf(stderr, "ERROR: failed to get parent element from max heap\n");
        return false;
    }

    // Bubble up if necessary
    while (parent <= element) {
        // swap if the parent is less than or equal to the element being inserted
        if (!dyn_arr_set(max_heap, parent_index, &element)) {
            fprintf(stderr, "ERROR: failed to set parent in max heap\n");
            return false;
        }

        if (!dyn_arr_set(max_heap, new_element_index, &parent)) {
            fprintf(stderr, "ERROR: failed to set element in max heap\n");
            return false;
        }

        // Move up the tree
        new_element_index = parent_index;
        if (!new_element_index) {
            // Reached the root, we're done
            return true;
        }

        parent_index = (new_element_index - 1) / 2;
        if (!dyn_arr_get(max_heap, parent_index, &parent)) {
            fprintf(stderr, "ERROR: failed to get parent element during bubble up\n");
            return false;
        }
    }

    return true;
}

/**
 * Deletes the maximum element from the max heap
 *
 * This function removes the root element (maximum) and restructures
 * the heap to maintain the max heap property by bubbling down.
 *
 * @param max_heap Pointer to the max heap
 * @param element Pointer to store the deleted element
 * @return true if successful, false if deletion failed
 */
bool max_heap_delete(max_heap_t *max_heap, int *element) {
    if (!max_heap) {
        fprintf(stderr, "ERROR: invalid max heap argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid output parameter\n");
        return false;
    }

    if (max_heap->is_empty) {
        fprintf(stderr, "ERROR: max heap is empty; can't delete\n");
        return false;
    }

    // handle the case when there's only one element
    if (max_heap->len == 1) {
        if (!dyn_arr_get(max_heap, 0, element)) {
            fprintf(stderr, "ERROR: could not get root element\n");
            return false;
        }

        if (!dyn_arr_pop(max_heap, NULL)) // remove the only element
        {
            fprintf(stderr, "ERROR: failed to pop element from max heap\n");
            return false;
        }

        return true;
    }

    // For multiple elements:
    // 1. Swap the root node with the last element in the array
    // 2. Pop the last element (doesn't make the max heap incomplete)
    // 3. Bubble down the new root to maintain heap property

    int root;
    int last;

    // Get the root and last elements
    if (!dyn_arr_get(max_heap, 0, &root)) {
        fprintf(stderr, "ERROR: failed to get root element\n");
        return false;
    }

    if (!dyn_arr_get(max_heap, max_heap->last_index, &last)) {
        fprintf(stderr, "ERROR: failed to get last element\n");
        return false;
    }

    // Swap root and last elements
    if (!dyn_arr_set(max_heap, 0, &last)) {
        fprintf(stderr, "ERROR: failed to set root element\n");
        return false;
    }

    if (!dyn_arr_set(max_heap, max_heap->last_index, &root)) {
        fprintf(stderr, "ERROR: failed to set last element\n");
        return false;
    }

    // Pop the last element (the original root) and store it in the output
    if (!dyn_arr_pop(max_heap, element)) {
        fprintf(stderr, "ERROR: failed to pop element from max heap\n");
        return false;
    }

    // Bubble down the new root to restore heap property
    size_t index = 0;

    while (true) {
        size_t left = 2 * index + 1; // Left child index
        size_t right = 2 * index + 2; // Right child index

        int current, left_val = -1, right_val = -1;

        // Get current node value
        if (!dyn_arr_get(max_heap, index, &current)) {
            fprintf(stderr, "ERROR: failed to get current element during bubble down\n");
            return false;
        }

        // Try to get left child value (if it exists)
        if (left <= max_heap->last_index) {
            if (!dyn_arr_get(max_heap, left, &left_val)) {
                fprintf(stderr, "ERROR: failed to get left child during bubble down\n");
                return false;
            }
        }

        // Try to get right child value (if it exists)
        if (right <= max_heap->last_index) {
            if (!dyn_arr_get(max_heap, right, &right_val)) {
                fprintf(stderr, "ERROR: failed to get right child during bubble down\n");
                return false;
            }
        }

        // Stop if no children or if we've reached a leaf node
        if (left > max_heap->last_index)
            break;

        size_t max_child_index;
        int max_child_val;

        // Find the larger child
        if (right > max_heap->last_index || left_val > right_val) {
            max_child_index = left;
            max_child_val = left_val;
        } else {
            max_child_index = right;
            max_child_val = right_val;
        }

        // If current is less than the larger child, swap and continue
        if (max_child_val > current) {
            // Swap current with the larger child
            if (!dyn_arr_set(max_heap, index, &max_child_val)) {
                fprintf(stderr, "ERROR: failed to set current element during bubble down\n");
                return false;
            }

            if (!dyn_arr_set(max_heap, max_child_index, &current)) {
                fprintf(stderr, "ERROR: failed to set child element during bubble down\n");
                return false;
            }

            index = max_child_index; // Move down to the child position
        } else {
            // Heap property is restored
            break;
        }
    }

    return true;
}

/**
 * Sorts the elements in the max heap
 *
 * This function implements the heap sort algorithm: it repeatedly
 * extracts the maximum element and places it at the end of the array.
 *
 * @param max_heap Pointer to the max heap
 * @return A sorted dynamic array containing the elements, or NULL if sorting failed
 */
dyn_arr_t *heap_sort(max_heap_t *max_heap) {
    if (!max_heap) {
        fprintf(stderr, "ERROR: invalid max heap argument\n");
        return NULL;
    }

    if (max_heap->is_empty) {
        fprintf(stderr, "ERROR: max heap is empty; can't sort\n");
        return NULL;
    }

    // Create a new array to store the sorted result
    dyn_arr_t *arr = dyn_arr_create(max_heap->len, sizeof(int), NULL);
    if (!arr) {
        fprintf(stderr, "ERROR: array creation failed: %s\n", strerror(errno));
        return NULL;
    }

    // Copy the max heap into the new array
    for (size_t index = 0; index <= max_heap->last_index; index++) {
        int element;
        if (!dyn_arr_get(max_heap, index, &element)) {
            fprintf(stderr, "ERROR: failed to get element during heap sort\n");
            dyn_arr_free(arr); // Clean up on error
            return NULL;
        }

        if (!dyn_arr_set(arr, index, &element)) {
            fprintf(stderr, "ERROR: failed to set element during heap sort\n");
            dyn_arr_free(arr); // Clean up on error
            return NULL;
        }
    }

    // Sort the array using the heap property
    // Extract elements one by one from the heap and place at the end
    size_t index = arr->last_index;
    while (index > 0) // Can't use >= 0 with size_t as it would cause underflow
    {
        int element;
        if (!max_heap_delete(arr, &element)) {
            fprintf(stderr, "ERROR: deletion failed during heap sort\n");
            dyn_arr_free(arr); // Clean up on error
            return NULL;
        }

        if (!dyn_arr_set(arr, index, &element)) {
            fprintf(stderr, "ERROR: failed to set element during final heap sort placement\n");
            dyn_arr_free(arr); // Clean up on error
            return NULL;
        }

        index--;
    }

    // Handle index 0 separately (since we can't go below 0 with size_t)
    if (arr->len > 0) {
        int element;
        if (!max_heap_delete(arr, &element)) {
            fprintf(stderr, "ERROR: deletion failed for final element during heap sort\n");
            dyn_arr_free(arr); // Clean up on error
            return NULL;
        }

        if (!dyn_arr_set(arr, 0, &element)) {
            fprintf(stderr, "ERROR: failed to set final element during heap sort\n");
            dyn_arr_free(arr); // Clean up on error
            return NULL;
        }
    }

    return arr;
}

/**
 * Helper function to maintain the max heap property
 *
 * This function assumes that the subtrees of the node at index are already
 * valid max heaps, but the node at index might violate the max heap property.
 * It fixes the violation by pushing the element down the heap.
 *
 * @param max_heap Pointer to the max heap
 * @param index Index of the node to sift down
 */
static void sift_down(max_heap_t *max_heap, long long index) {
    if (!max_heap || index < 0 || (size_t) index > max_heap->last_index) {
        return; // Invalid arguments
    }

    int element;
    if (!dyn_arr_get(max_heap, index, &element)) {
        fprintf(stderr, "ERROR: failed to get element during sift down\n");
        return;
    }

    size_t left_child_index;
    size_t right_child_index;
    size_t max_child_index;

    int left_child;
    int right_child;
    int max_child;

    left_child_index = 2 * index + 1;
    right_child_index = 2 * index + 2;

    // If there is no left child, there is no right child too and we are done
    if (left_child_index > max_heap->last_index) {
        return;
    }

    if (!dyn_arr_get(max_heap, left_child_index, &left_child)) {
        fprintf(stderr, "ERROR: failed to get left child during sift down\n");
        return;
    }

    // If there is a left child, check if there is a right child
    if (right_child_index > max_heap->last_index) {
        // There is no right child
        max_child_index = left_child_index;
        max_child = left_child;
    } else {
        // There is a right child
        if (!dyn_arr_get(max_heap, right_child_index, &right_child)) {
            fprintf(stderr, "ERROR: failed to get right child during sift down\n");
            return;
        }

        // Choose the larger child
        if (left_child > right_child) {
            max_child_index = left_child_index;
            max_child = left_child;
        } else {
            max_child_index = right_child_index;
            max_child = right_child;
        }
    }

    // We got the max child, check if we need to swap
    if (max_child <= element) {
        // Already a heap, no need to sift down further
        return;
    } else {
        // Swap with max child and call sift_down on it recursively
        if (!dyn_arr_set(max_heap, index, &max_child)) {
            fprintf(stderr, "ERROR: failed to set current element during sift down\n");
            return;
        }

        if (!dyn_arr_set(max_heap, max_child_index, &element)) {
            fprintf(stderr, "ERROR: failed to set child element during sift down\n");
            return;
        }

        sift_down(max_heap, (long long) max_child_index);
    }
}

/**
 * Converts a binary tree to a max heap
 *
 * This function first converts the binary tree to an array representation,
 * then applies the heapify algorithm to transform it into a max heap.
 *
 * @param binary_tree Pointer to the binary tree
 * @return A pointer to the max heap, or NULL if conversion failed
 */
max_heap_t *conv_to_max_heap(binary_tree_t *binary_tree) {
    if (!binary_tree || !binary_tree->top_node) {
        fprintf(stderr, "ERROR: invalid binary tree\n");
        return NULL;
    }

    // Convert binary tree to array representation
    dyn_arr_t *arr = conv_to_arr(binary_tree);
    if (!arr) {
        fprintf(stderr, "ERROR: cannot convert to array representation\n");
        return NULL;
    }

    // For empty or single-element trees, no heapify needed
    if (arr->is_empty || arr->len == 1) {
        return (max_heap_t *) arr;
    }

    // Heapify the array from bottom up (Floyd's algorithm)
    // Start from the parent of the last node and move up
    long long index = (long long) (arr->last_index - 1) / 2;

    while (index >= 0) // If we use size_t, we'll enter infinite loop when wrapping around
    {
        sift_down(arr, index);
        index--;
    }

    return (max_heap_t *) arr;
}

/**
 * Frees all memory associated with a max heap
 *
 * @param max_heap Pointer to the max heap
 */
void max_heap_free(max_heap_t *max_heap) {
    if (!max_heap) {
        return;
    }

    dyn_arr_free(max_heap);
}
