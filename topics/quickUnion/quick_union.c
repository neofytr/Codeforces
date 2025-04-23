//
// Created by raj on 23/4/25.
//

#include "quick_union.h"
#include <stdlib.h>
#include <stdio.h>

tree_t *create_tree(size_t size) {
    tree_t *tree = malloc(sizeof(tree_t));
    if (!tree) {
        fprintf(stderr, "ERROR: failed to allocate the tree structure: %s\n");
        return NULL;
    }

    tree->arr = malloc(sizeof(size_t) * size);
    if (!tree->arr) {
        fprintf(stderr, "ERROR: failed to allocate the element array in the tree structure: %s\n");
        free(tree);
        return NULL;
    }

    tree->size = malloc(sizeof(size_t) * size);
    if (!tree->size) {
        fprintf(stderr, "ERROR: failed to allocate the size array in the tree structure: %s\n");
        free(tree->arr);
        free(tree);
        return NULL;
    }

    for (size_t index = 0; index < size; index++) {
        tree->arr[index] = index; // all elements initially are in their own connected sets
        tree->size[index] = 1; // initially all trees are of size 1
    }

    tree->len = size;

    return tree;
}

inline size_t getRoot(const tree_t *tree, size_t p) {
    size_t temp = p;
    while (p != tree->arr[p]) {
        p = tree->arr[p];
    }

    while (temp != tree->arr[temp]) {
        const size_t parent = tree->arr[temp];
        tree->arr[temp] = p;
        temp = parent;
    }

    return p;
}

bool do_union(tree_t *tree, size_t p, size_t q) {
    if (!tree) {
        fprintf(stderr, "ERROR: invalid tree structure argument\n");
        return false;
    }

    if (p >= tree->len || q >= tree->len) {
        fprintf(stderr, "ERROR: one or both of the arguments p and q are out of bounds\n");
        fprintf(stderr, "ERROR: max value of an object -> %zu; p -> %zu; q -> %zu\n", tree->len, p, q);
        return false;
    }

    const size_t root_p = getRoot(tree, p);
    const size_t root_q = getRoot(tree, q);

    const size_t size_p = tree->size[root_p];
    const size_t size_q = tree->size[root_q];

    if (size_p > size_q) {
        tree->arr[root_q] = root_p;
        tree->size[root_p] += size_q;
    } else {
        tree->arr[root_p] = root_q;
        tree->size[root_q] += size_p;
    }

    return true;
}

bool find(const tree_t *tree, size_t p, size_t q) {
    if (!tree) {
        fprintf(stderr, "ERROR: invalid tree structure argument\n");
        return false;
    }

    if (p >= tree->len || q >= tree->len) {
        fprintf(stderr, "ERROR: one or both of the arguments p and q are out of bounds\n");
        fprintf(stderr, "ERROR: max value of an object -> %zu; p -> %zu; q -> %zu\n", tree->len, p, q);
        return false;
    }

    return getRoot(tree, p) == getRoot(tree, q);
}
