#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

typedef struct binary_node_ binary_node_t;
typedef struct binary_tree_ binary_tree_t;

struct binary_node_
{
    binary_node_t *left_node;
    binary_node_t *right_node;
    int data;
};

struct binary_tree_
{
    binary_node_t *top_node;
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
    struct search_t
    {
        binary_node_t *binary_node;
        size_t index;
    };

    queue_t *queue = create_queue(sizeof(struct search_t), NULL, NULL);
    if (!queue)
    {
        fprintf(stderr, "ERROR: tree traversal failed\n");
        return NULL;
    }

    struct search_t root = {.binary_node = binary_tree->top_node, .index = 0};
    enqueue(queue, &root);

    struct search_t temp;
    binary_node_t *binary_node;

    while (!isEmpty(queue))
    {
        dequeue(queue, &temp); // the data is copied into temp upon dequeue (and the queue's copy is freed)
        binary_node = temp.binary_node;
        arr[temp.index] = binary_node->data;

        if (binary_node->left_node) // left node is available, put it into the queue
        {
            root.binary_node = binary_node->left_node;
            root.index = temp.index * 2;
            enqueue(queue, &root);
        }

        if (binary_node->right_node)
        {
            root.binary_node = binary_node->right_node;
            root.index = temp.index * 2 + 1;
            enqueue(queue, &root);
        }
    }

    destroy_queue(queue);
    return arr;
}
