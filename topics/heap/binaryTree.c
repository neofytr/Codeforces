#include <stdlib.h>
#include "queue.h"
#include "dynarr.h"

typedef struct binary_node_
{
    struct binart_node_ *left_node;
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
