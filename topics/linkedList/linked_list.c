//
// Created by raj on 22/4/25.
//

#include "linked_list.h"

list_t *list_create() {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    if (!list) {
        fprintf(stderr, "ERROR: cannot allocate list: %s\n", strerror(errno));
        return NULL;
    }

    list->head = -1; // is empty initially
    list->hole_index = -1;
    list->list_len = 0;

    return list;
}

bool list_empty(const list_t *list) {
    return !list->list_len;
}

bool list_insert(list_t *list, const int index, const TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid element argument\n");
        return false;
    }

    if (index >= list->list_len) {
        fprintf(stderr, "ERROR: index out of bounds\n");
        return false;
    }

    if (list->list_len >= MAX_LIST_LEN) {
        fprintf(stderr, "ERROR: list is full\n");
        return false;
    }

    // handle the case when list is empty
    if (list_empty(list)) {
        // list is empty
        list->head = 0;
        // list has its own copy of the element
        memcpy((void *) &list->arr[0], element, sizeof(TYPE)); // place element into the list
        list->next[0] = -1;
        list->list_len++;
        return true;
    }

    // handle the case when index is 0
    if (!index) {
        // insertion at the head of the list
        int index_to_insert_at;
        if (list->hole_index == -1) {
            // there are no holes
            index_to_insert_at = list->list_len++;
        } else {
            // there are holes
            index_to_insert_at = list->holes[list->hole_index--];
        }

        // insert
        memcpy((void *) &list->arr[index_to_insert_at], (void *) element, sizeof(TYPE));

        // the new element points to the previous head
        list->next[index_to_insert_at] = list->head;

        // update the head
        list->hole_index = index_to_insert_at;

        return true;
    }

    // index >= 1 from here on out
    int curr = list->head;
    int traversed = 0;

    while (curr != -1) {
        if (traversed == index - 1) {
            // reached the node just before the insertion point

            int index_to_insert_at;
            if (list->hole_index == -1) {
                // there are no holes
                index_to_insert_at = list->list_len++;
            } else {
                // there are holes
                index_to_insert_at = list->holes[list->hole_index--];
            }

            // insert
            memcpy((void *) &list->arr[index_to_insert_at], (void *) element, sizeof(TYPE));

            // the element at index - 1 now points to this new element and the element that
            // it previously pointed to will be pointed to by this new element
            list->next[index_to_insert_at] = list->next[curr];
            list->next[curr] = index_to_insert_at;

            return true;
        }

        traversed++;
        curr = list->next[curr];
    }

    // should never reach here
    fprintf(stderr, "ERROR: some tampering is done with the list_t structure provided\n");
    return false;
}

bool list_remove(list_t *list, const int index, TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    // check if list is empty
    if (list_empty(list)) {
        fprintf(stderr, "ERROR: list is empty; can't delete\n");
        return false;
    }

    // check if index is 0
    // this is removal at the head
    if (!index) {
        // change the list head to point to the next element after head
        // it's impossible for list->holes to be full
        list->holes[list->hole_index++] = list->head;
        list->head = list->next[list->head];
        return true;
    }

    // index >= 1 from now on
    int curr = list->head;
    int traversed = 0;
    while (curr != -1) {
        if (traversed == index - 1) {
            // this is the element just before the one being removed
        }

        traversed++;
        curr = list->next[curr];
    }

    return false;
}
