#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "queue.h"
#include "dynarr.h"

typedef struct binary_node_
{
    struct binary_node_ *left_node;
    struct binary_node_ *right_node;
    int node_data;
} binary_node_t;

typedef struct binary_tree_
{
    binary_node_t *top_node;
    size_t size;
    size_t height;
} binary_tree_t;

// a full binary tree is the one which has the maximum number of nodes possible in it's height
// in a binary tree of height h, the maximum number of nodes possible is (2 ^ (h + 1) - 1)
// the number of levels in a binary tree is one more than it's height

// a full binary tree of height 1 is complete
// a binary tree of height h >= 2 is said to be complete if
// 1. it's full until a height of h - 1
// 2. the last level of the tree has elements filled from left to right

// or equivalently, we can say a binary tree is complete if it doesn't have any holes
// in it's array representation

// To represent a binary tree as an array, insert its nodes level by level,
// starting from the root (index 0). At each level, insert nodes from left to right.
// For a node at index i:
//   - Left child is at index 2*i + 1
//   - Right child is at index 2*i + 2
//   - Parent is at index (i - 1) / 2 (only if i > 0)
// This continues until all levels of the tree are filled.

dyn_arr_t *conv_to_arr(binary_tree_t *binary_tree)
{
    if (!binary_tree || !binary_tree->top_node)
    {
        fprintf(stderr, "ERROR: invalid binary tree\n");
        return NULL;
    }

    size_t max_size = (1ULL << (binary_tree->height + 1)) - 1;

    struct search_t
    {
        binary_node_t *binary_node;
        size_t index;
    };

    dyn_arr_t *arr = dyn_arr_create(max_size, sizeof(binary_tree->top_node->node_data), NULL);
    if (!arr)
    {
        fprintf(stderr, "ERROR: dynamic array creation failed: %s\n", strerror(errno));
        return NULL;
    }

    // traverse the binary tree in BFS

    queue_t *queue = create_queue(sizeof(struct search_t), NULL, NULL);
    if (!queue)
    {
        fprintf(stderr, "ERROR: cannot traverse the binary tree\n");
        return NULL;
    }

    struct search_t root = {.binary_node = binary_tree->top_node, .index = 0};
    enqueue(queue, (void *)&root);

    while (!isEmpty(queue))
    {
        struct search_t current;
        dequeue(queue, &current);
        }
}