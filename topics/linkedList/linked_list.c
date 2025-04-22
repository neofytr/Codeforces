#include "linked_list.h"

list_t *list_create() {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    if (!list) {
        fprintf(stderr, "ERROR: list creation failed: %s\n", strerror(errno));
        return NULL;
    }

    list->head = NULL;
    list->len = 0;

    return list;
}

bool list_empty(list_t *list) {
    return !list || !list->head;
}

bool list_insert(list_t *list, int index, const TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }
}
