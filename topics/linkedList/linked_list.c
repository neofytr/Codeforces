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
        dyn_arr_set(list->arr, 0, element);
    }
    return true;
}
