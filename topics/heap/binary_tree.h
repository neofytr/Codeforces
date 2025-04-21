#ifndef BINARY_TREE_H
#define BINARY_TREE_H

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

dyn_arr_t *conv_to_arr(binary_tree_t *binary_tree);


#endif