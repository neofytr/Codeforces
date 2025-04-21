#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

typedef struct node_ node_t;
typedef struct binary_tree_ binary_tree_t;

struct node_
{
    node_t *left_node;
    node_t *right_node;
    int data;
};

struct binary_tree_
{
    node_t *top_node;
    size_t size;
    size_t height;
};

int *conv_to_binary_arr(binary_tree_t *binary_tree)
{
    if (!binary_tree || !binary_tree->top_node)
    {
        fprintf(stderr, "ERROR: invalid binary tree\n");
        return NULL;
    }

    size_t max_nodes = (1ULL << (binary_tree->height + 1)) - 1;
    int *arr = (int *)calloc(sizeof(int), max_nodes);
    if (!arr)
    {
        fprintf(stderr, "ERROR: array allocation failed: %s\n", strerror(errno));
        return NULL;
    }

    // traverse the tree level wise from left to right (BFS)

    queue_t *queue = create_queue();
    if (!queue)
    {
        fprintf(stderr, "ERROR: dfs on the tree failed\n");
        return NULL;
    }

    search_t search = {binary_tree->top_node->data, 0};
    enqueue(queue, search);

    // removal at front of the queue
    // insertion at back of the queue
    while (!isEmpty(queue))
    {
    }
}
