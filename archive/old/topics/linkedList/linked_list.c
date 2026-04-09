#include "linked_list.h"
#include "memalloc.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

list_t *list_create(size_t min_size) {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    if (!list) {
        fprintf(stderr, "ERROR: list creation failed: %s\n", strerror(errno));
        return NULL;
    }

    if (!MEM_INIT(min_size)) {
        fprintf(stderr, "ERROR: memory pool initialization failed\n");
        free(list);
        return NULL;
    }

    list->head = NULL;
    list->len = 0;

    return list;
}

bool list_empty(const list_t *list) {
    return !list || !list->head;
}

bool list_remove(list_t *list, int index, TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    // handle the case when list is empty
    if (list_empty(list)) {
        fprintf(stderr, "ERROR: list is empty; can't perform delete\n");
        return false;
    }

    // handle the case when the list is out of bounds
    if (index >= list->len) {
        fprintf(stderr, "ERROR: index %d out of range\n", index);
        return false;
    }

    // handle deletion at index 0
    if (!index) {
        node_t *node = list->head;

        // set the head node to the next node of the current head
        list->head = list->head->next;

        // free the node being deleted
        if (element) {
            memcpy((void *) element, (void *) &node->data, sizeof(TYPE));
        }
        MEM_FREE(node);
        list->len--;
        return true;
    }

    // list is non-empty and index >= 1
    node_t *curr = list->head;
    int traversed = 0;

    while (curr) {
        if (traversed == index - 1) {
            // we are at the node just before the node being deleted;
            node_t *next = curr->next;

            // set the current node to point to next_to_next and free next
            curr->next = next->next;
            if (element) {
                memcpy((void *) element, (void *) &next->data, sizeof(TYPE));
            }
            MEM_FREE(next);
            list->len--;
            return true;
        }

        traversed++;
        curr = curr->next;
    }

    // this should never be reached
    fprintf(stderr, "ERROR: the list_t structure has been tampered with\n");
    return false;
}

bool list_append(list_t *list, const TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    return list_insert(list, list->len, element);
}

bool list_pop(list_t *list, TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    return list_remove(list, list->len - 1, element);
}

bool list_get(list_t *list, int index, TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid element argument\n");
        return false;
    }

    // handle the case when list is empty
    if (list_empty(list)) {
        fprintf(stderr, "ERROR: list is empty; can't perform delete\n");
        return false;
    }

    // handle the case when the list is out of bounds
    if (index >= list->len) {
        fprintf(stderr, "ERROR: index %d out of range\n", index);
        return false;
    }

    // list is not empty now onwards
    node_t *curr = list->head;
    int traversed = 0;

    while (curr) {
        if (traversed == index) {
            memcpy((void *) element, (void *) &curr->data, sizeof(TYPE));
            return true;
        }

        traversed++;
        curr = curr->next;
    }

    // this should never be reached
    fprintf(stderr, "ERROR: the list_t structure has been tampered with\n");
    return false;
}

bool list_insert(list_t *list, int index, const TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid element argument\n");
        return false;
    }

    // handle the case when list is empty
    if (list_empty(list)) {
        if (!index) {
            list->head = (node_t *) MEM_ALLOC(sizeof(node_t));
            if (!list->head) {
                fprintf(stderr, "ERROR: error creating new node: %s\n", strerror(errno));
                return false;
            }

            list->head->next = NULL;
            memcpy((void *) &list->head->data, element, sizeof(TYPE));
            list->len++;
            return true;
        } else {
            fprintf(stderr, "ERROR: list is empty; cannot insert at index %d\n", index);
            return false;
        }
    }

    // strictly can insert upto just after the list, i.e, index == list.len
    if (index > list->len) {
        fprintf(stderr, "ERROR: index %d out of bounds\n", index);
        return false;
    }

    // there is at least one node, the head node at least,

    // handle the case when list is non-empty and index == 0
    if (!index) {
        node_t *new_node = (node_t *) MEM_ALLOC(sizeof(node_t));
        if (!new_node) {
            fprintf(stderr, "ERROR: error creating new node: %s\n", strerror(errno));
            return false;
        }

        memcpy((void *) &new_node->data, (void *) element, sizeof(TYPE));

        // make the current head the next node of the new node
        // also, make the new node the head node

        new_node->next = list->head;
        list->head = new_node;
        list->len++;

        return true;
    }

    // index >= 1 now onwards
    node_t *curr = list->head;
    int traversed = 0;

    while (curr) {
        if (traversed == index - 1) {
            // this is the position just before insertion
            node_t *next = curr->next;
            node_t *new_node = (node_t *) MEM_ALLOC(sizeof(node_t));
            if (!new_node) {
                fprintf(stderr, "ERROR: error creating new node: %s\n", strerror(errno));
                return false;
            }

            memcpy((void *) &new_node->data, (void *) element, sizeof(TYPE));

            // set the new node to the next node of the current node
            // also set the next node of the new node to the next node of the current node
            curr->next = new_node;
            new_node->next = next;

            list->len++;
            return true;
        }

        traversed++;
        curr = curr->next;
    }

    // this should never be reached

    fprintf(stderr, "ERROR: list structure has been tampered with\n");
    return false;
}
