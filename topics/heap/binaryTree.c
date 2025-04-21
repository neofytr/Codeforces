#include <cstring>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node_ node_t;
typedef struct binary_tree_ binary_tree_t;

struct node_ {
    node_t *left_node;
    node_t *right_node;
    int data;
};

struct binary_tree_ {
    node_t *top_node;
    size_t size;
    size_t height;
};

int *conv_to_binary_arr(binary_tree_t *binary_tree) {
    if (!binary_tree || !binary_tree->top_node) {
        fprintf(stderr, "ERROR: invalid binary tree\n");
        return NULL;
    }

    int *arr = (int *) calloc(-1, sizeof(int) * ((1ULL << (binary_tree->height + 1)) - 1));
    if (!arr) {
        fprintf(stderr, "ERROR: array allocation failed: %s\n", strerror(errno));
        return NULL;
    }

    size_t num_of_levels = binary_tree->height + 1;
    for (size_t level = 0; level < num_of_levels; ++level) {

    }
}
