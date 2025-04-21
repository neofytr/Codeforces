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
    int *arr = (int *)calloc(max_nodes, sizeof(int));
    if (!arr)
    {
        fprintf(stderr, "ERROR: array allocation failed: %s\n", strerror(errno));
        return NULL;
    }

    struct search_t
    {
        binary_node_t *binary_node;
        size_t index;
    };

    // we just free the entire copy of the search_t structure that the queue has
    // and not the binary node struct pointer we have inside it
    // so we use generic free on the search_t struct and thus NULL is passed
    queue_t *queue = create_queue(sizeof(struct search_t), NULL, NULL);
    if (!queue)
    {
        fprintf(stderr, "ERROR: tree traversal failed\n");
        free(arr);
        return NULL;
    }

    struct search_t root = {.binary_node = binary_tree->top_node, .index = 0};
    enqueue(queue, &root);

    while (!isEmpty(queue))
    {
        struct search_t temp;
        dequeue(queue, &temp);

        arr[temp.index] = temp.binary_node->data;

        if (temp.binary_node->left_node)
        {
            struct search_t left = {
                .binary_node = temp.binary_node->left_node,
                .index = temp.index * 2};
            enqueue(queue, &left);
        }

        if (temp.binary_node->right_node)
        {
            struct search_t right = {
                .binary_node = temp.binary_node->right_node,
                .index = temp.index * 2 + 1};
            enqueue(queue, &right);
        }
    }

    destroy_queue(queue);
    return arr;
}
