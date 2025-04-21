#include "binary_tree.h"

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

        binary_node_t *binary_node = current.binary_node;
        dyn_arr_set(arr, current.index, &binary_node->node_data); // add to the array at the correct position

        if (binary_node->left_node)
        {
            // if there is left node, add it to the queue
            struct search_t left_node_temp =
                {
                    .binary_node = binary_node->left_node,
                    .index = 2 * current.index + 1,
                };

            enqueue(queue, &left_node_temp);
        }

        if (binary_node->right_node)
        {
            // there is right node, add it to the queue
            struct search_t right_node_temp =
                {
                    .binary_node = binary_node->right_node,
                    .index = 2 * current.index + 2,
                };

            enqueue(queue, &right_node_temp);
        }
    }
}