#include "linked_list.h"

#define MIN_SIZE (1024)

list_t *list_create() {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    if (!list) {
        fprintf(stderr, "ERROR: list allocation failed: %s\n", strerror(errno));
        return NULL;
    }

    list->arr = dyn_arr_create(MIN_SIZE, sizeof(TYPE), NULL);
    if (!list->arr) {
        fprintf(stderr, "ERROR: list allocation failed: %s\n", strerror(errno));
        free(list);
        return NULL;
    }

    list->next = dyn_arr_create(MIN_SIZE, sizeof(size_t), NULL);
    if (!list->next) {
        fprintf(stderr, "ERROR: list allocation failed: %s\n", strerror(errno));
        free(list);
        return NULL;
    }

    return list;
}

bool list_insert(list_t *list, int index, TYPE *element) {
    if (!list || !list->arr || !list->next) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid element argument\n");
        return false;
    }

    if (list->arr->is_empty) {
        // dyn_arr_set will copy arr.num bytes from the location element and store inside it internally (as a copy) at index
        dyn_arr_set(list->arr, 0, element);
        const int next = -1;
        dyn_arr_set(list->next, 0, &next);
        return true;
    }

    if (index > list->arr->last_index) {
        fprintf(stderr, "ERROR: index out of bounds of the list\n");
        return false;
    }

    dyn_arr_append(list->arr, element);
    if (index > 0) {
        // set the element at the position index - 1 to point to the new element
        dyn_arr_set(list->next, index - 1, &list->arr->last_index);
    }

    // set the new element to point to the element at index
    dyn_arr_set(list->next, list->arr->last_index, &index);

    // this completes the insertion
    return true;
}
