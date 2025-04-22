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

    list->head_index = 0;

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

    // handle the empty list case
    if (list->arr->is_empty) {
        // dyn_arr_set will copy arr.num bytes from the location element and store inside it internally (as a copy) at index
        if (!index) {
            dyn_arr_set(list->arr, 0, element);
            const int next = -1;
            dyn_arr_set(list->next, 0, &next);
            return true;
        } else {
            fprintf(stderr, "ERROR: can't insert at index %d; list is empty\n", index);
            return false;
        }
    }

    // handle the index zero case
    if (!index) {
        // add the new element to the end and set it to point to the old
        // list head
        dyn_arr_append(list->arr, element);
        dyn_arr_append(list->next, &list->head_index);

        // update the head_index
        list->head_index = list->arr->last_index;
        return true;
    }

    // handle the rest of the cases

    int traversed = 0;
    int curr = list->head_index;
    int next;

    do {
        traversed++;
        if (traversed == index - 1) {
            // insert the new element at the end
            dyn_arr_append(list->arr, element);

            // set the new element to point to the previous element at position index
            int next_to_new;
            dyn_arr_get(list->next, curr, &next_to_new);
            dyn_arr_append(list->next, &next_to_new);

            // set the element at position index - 1 to point to the new element
            dyn_arr_set(list->next, curr, &list->arr->last_index);
            return true;
        }

        dyn_arr_get(list->next, curr, &next);
        curr = next;
    } while (curr != -1);

    fprintf(stderr, "ERROR: index %d out of bounds\n", index);

    return false;
}

bool list_remove(list_t *list, int index, TYPE *element) {
    if (!list || !list->arr || !list->next) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }
}
