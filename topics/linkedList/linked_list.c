#include "linked_list.h"

#define MIN_SIZE (1024)

list_t *list_create() {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    if (!list) {
        fprintf(stderr, "error: list allocation failed: %s\n", strerror(errno));
        return NULL;
    }

    list->arr = dyn_arr_create(MIN_SIZE, sizeof(TYPE), NULL);
    if (!list->arr) {
        fprintf(stderr, "error: list allocation failed: %s\n", strerror(errno));
        free(list);
        return NULL;
    }

    list->next = dyn_arr_create(MIN_SIZE, sizeof(size_t), NULL);
    if (!list->next) {
        fprintf(stderr, "error: list allocation failed: %s\n", strerror(errno));
        dyn_arr_free(list->arr); // Fixed: Free already allocated array
        free(list);
        return NULL;
    }

    list->holes = dyn_arr_create(MIN_SIZE, sizeof(size_t), NULL);
    if (!list->holes) {
        fprintf(stderr, "error: list allocation failed: %s\n", strerror(errno));
        dyn_arr_free(list->arr); // Fixed: Free already allocated arrays
        dyn_arr_free(list->next);
        free(list);
        return NULL;
    }

    list->head_index = -1;
    return list;
}

bool list_insert(list_t *list, int index, TYPE *element) {
    if (!list || !list->arr || !list->next) {
        fprintf(stderr, "error: invalid list argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "error: invalid element argument\n");
        return false;
    }

    // handle the empty list case
    if (list->head_index == -1) {
        // dyn_arr_set will copy arr.num bytes from the location element and store inside it internally (as a copy) at index
        if (!index) {
            dyn_arr_set(list->arr, 0, element);
            const int next = -1;
            dyn_arr_set(list->next, 0, &next);
            list->head_index = 0; // Fixed: Set head_index
            return true;
        } else {
            fprintf(stderr, "error: can't insert at index %d; list is empty\n", index);
            return false;
        }
    }

    // handle the index zero case
    if (!index) {
        // add the new element to a free index (or at the end if no free index) and set it to point to the old
        // list head
        int index_to_add_to;
        if (list->holes->is_empty) {
            dyn_arr_append(list->arr, element);
            dyn_arr_append(list->next, &list->head_index);
            index_to_add_to = list->arr->last_index;
        } else {
            dyn_arr_pop(list->holes, &index_to_add_to);
            dyn_arr_set(list->arr, index_to_add_to, element);
            dyn_arr_set(list->next, index_to_add_to, &list->head_index);
        }

        // update the head_index
        list->head_index = index_to_add_to;
        return true;
    }

    // handle the rest of the cases
    int traversed = 0;
    int curr = list->head_index;
    int next;

    do {
        traversed++;
        if (traversed == index - 1) {
            int index_to_insert_at;
            if (list->holes->is_empty) {
                dyn_arr_append(list->arr, element);
                index_to_insert_at = list->arr->last_index;

                // also need to append to the next array
                int dummy = -1;
                dyn_arr_append(list->next, &dummy);
            } else {
                dyn_arr_pop(list->holes, &index_to_insert_at);
                dyn_arr_set(list->arr, index_to_insert_at, element);
            }

            // set the new element to point to the previous element at position index
            int next_to_new;
            dyn_arr_get(list->next, curr, &next_to_new);
            dyn_arr_set(list->next, index_to_insert_at, &next_to_new);

            // set the element at position index - 1 to point to the new element
            dyn_arr_set(list->next, curr, &index_to_insert_at);
            return true;
        }

        dyn_arr_get(list->next, curr, &next);
        curr = next;
    } while (curr != -1);

    fprintf(stderr, "error: index %d out of bounds\n", index);

    return false;
}

bool list_remove(list_t *list, int index, TYPE *element) {
    if (!list || !list->arr || !list->next) {
        fprintf(stderr, "error: invalid list argument\n");
        return false;
    }

    // handle the empty list case
    if (list->head_index == -1) {
        fprintf(stderr, "error: can't remove at index %d; list is empty\n", index);
        return false;
    }

    // handle the index zero case
    if (!index) {
        // save the element value if requested
        if (element) {
            dyn_arr_get(list->arr, list->head_index, element);
        }

        // get the index after the head, make the head point to it
        int next_to_head;
        dyn_arr_get(list->next, list->head_index, &next_to_head);

        // we created a hole
        dyn_arr_append(list->holes, &list->head_index);
        list->head_index = next_to_head;
        return true;
    }

    // handle the rest of the cases
    int traversed = 0;
    int curr = list->head_index;
    int next;

    do {
        traversed++;
        if (traversed == index - 1) {
            // get the index of element to be deleted
            dyn_arr_get(list->next, curr, &next);
            if (next == -1) {
                fprintf(stderr, "error: index %d out of bounds\n", index);
                return false;
            }

            // save the element value if requested
            if (element) {
                dyn_arr_get(list->arr, next, element);
            }

            // we have created a hole
            dyn_arr_append(list->holes, &next);

            // get the next to next
            int next_to_next;
            dyn_arr_get(list->next, next, &next_to_next);

            // set the element at curr to point to this next to next
            dyn_arr_set(list->next, curr, &next_to_next);
            return true;
        }

        dyn_arr_get(list->next, curr, &next);
        curr = next;
    } while (curr != -1);

    fprintf(stderr, "error: index %d out of bounds\n", index);

    return false;
}

bool list_append(list_t *list, TYPE *element) {
    if (!list || !list->arr || !list->next) {
        fprintf(stderr, "error: invalid list argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "error: invalid element argument\n");
        return false;
    }

    // handle the empty list case
    if (list->head_index == -1) {
        const int index_to_use = 0;
        dyn_arr_set(list->arr, index_to_use, element);
        const int next = -1;
        dyn_arr_set(list->next, index_to_use, &next);
        list->head_index = index_to_use;
        return true;
    }

    // find the last element in the list
    int curr = list->head_index;
    int next;

    do {
        dyn_arr_get(list->next, curr, &next);
        if (next == -1) {
            // we found the last element
            int new_index;

            // check for holes first
            if (!list->holes->is_empty) {
                dyn_arr_pop(list->holes, &new_index);
                dyn_arr_set(list->arr, new_index, element);
            } else {
                // add the new element to the end
                dyn_arr_append(list->arr, element);
                new_index = list->arr->last_index;
            }

            // set the last element to point to the new one
            dyn_arr_set(list->next, curr, &new_index);

            // set the new element's next to -1
            const int end = -1;

            // check if we need to append or set
            if (new_index == list->arr->last_index) {
                dyn_arr_append(list->next, &end);
            } else {
                dyn_arr_set(list->next, new_index, &end);
            }

            return true;
        }
        curr = next;
    } while (curr != -1);

    // should never reach here if the list is properly formed
    fprintf(stderr, "error: list seems corrupted\n");
    return false;
}

bool list_pop(list_t *list, TYPE *element) {
    if (!list || !list->arr || !list->next) {
        fprintf(stderr, "error: invalid list argument\n");
        return false;
    }

    // handle the empty list case
    if (list->head_index == -1) {
        fprintf(stderr, "error: can't pop from empty list\n");
        return false;
    }

    // find the second to last element
    int prev = -1;
    int curr = list->head_index;
    int next;

    do {
        dyn_arr_get(list->next, curr, &next);
        if (next == -1) {
            // curr is the last element
            // copy the element if requested
            if (element) {
                dyn_arr_get(list->arr, curr, element);
            }

            // Add the freed index to holes
            dyn_arr_append(list->holes, &curr);

            // handle the case where there's only one element
            if (prev == -1) {
                list->head_index = -1;
                return true;
            }

            // update the previous element to point to nothing
            const int end = -1;
            dyn_arr_set(list->next, prev, &end);
            return true;
        }
        prev = curr;
        curr = next;
    } while (curr != -1);

    // should never reach here if the list is properly formed
    fprintf(stderr, "error: list seems corrupted\n");
    return false;
}

bool list_empty(list_t *list) {
    if (!list || !list->arr) {
        fprintf(stderr, "error: invalid list argument\n");
        return true; // returning true as it's technically empty
    }

    return list->head_index == -1;
}

bool list_free(list_t *list) {
    if (!list) {
        fprintf(stderr, "error: invalid list argument\n");
        return false;
    }

    if (list->arr) {
        dyn_arr_free(list->arr);
    }

    if (list->next) {
        dyn_arr_free(list->next);
    }

    if (list->holes) {
        dyn_arr_free(list->holes);
    }

    free(list);
    return true;
}
