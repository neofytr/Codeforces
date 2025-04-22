#include "linked_list.h"

#define MIN_SIZE (1024)

list_t *list_create() {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    if (!list) {
        fprintf(stderr, "ERROR: list allocation failed: %s\n", strerror(errno));
        return NULL;
    }

    list->arr = dyn_arr_create(MIN_SIZE, sizeof());
}
