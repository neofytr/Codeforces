//
// Created by raj on 23/4/25.
//

#ifndef QUICK_UNION_H
#define QUICK_UNION_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t *arr; // arr[r] tells the element to which r points to in its tree
    size_t *size; // size[r] tells the size of the tree rooted at r
    size_t len;
} tree_t;

tree_t *create_tree(size_t size);

bool do_union(tree_t *tree, size_t p, size_t q);

bool find(const tree_t *tree, size_t p, size_t q);

#endif //QUICK_UNION_H
