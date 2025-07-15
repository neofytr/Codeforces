#include "linked_list.h"

bool list_append(list_t *list, TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid element argument\n");
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
        memcpy((void *) &list->arr[0], element, sizeof(TYPE));
        list->next[0] = -1;
        list->list_len++;
        return true;
    }

    // find the last element
    int curr = list->head;
    while (list->next[curr] != -1) {
        curr = list->next[curr];
    }

    // now curr is the index of the last element
    int index_to_insert_at;
    if (list->hole_index == -1) {
        // there are no holes
        index_to_insert_at = list->list_len++;
    } else {
        // there are holes
        index_to_insert_at = list->holes[list->hole_index--];
    }

    // insert
    memcpy((void *) &list->arr[index_to_insert_at], element, sizeof(TYPE));

    // link the new element to the end of the list
    list->next[curr] = index_to_insert_at;
    list->next[index_to_insert_at] = -1;

    return true;
}

bool list_pop(list_t *list, TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid element argument\n");
        return false;
    }

    // check if list is empty
    if (list_empty(list)) {
        fprintf(stderr, "ERROR: list is empty; can't pop\n");
        return false;
    }

    // find the last element and the one before it
    int curr = list->head;
    int prev = -1;

    while (list->next[curr] != -1) {
        prev = curr;
        curr = list->next[curr];
    }

    // now curr is the index of the last element
    // copy the element if requested
    memcpy(element, &list->arr[curr], sizeof(TYPE));

    // remove the last element
    if (prev == -1) {
        // only one element in the list
        list->head = -1;
    } else {
        // more than one element
        list->next[prev] = -1;
    }

    // add the removed index to holes
    list->holes[++list->hole_index] = curr;
    list->list_len--;

    return true;
}

bool list_delete(list_t *list, TYPE *element) {
    if (!list) {
        fprintf(stderr, "ERROR: invalid list argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid element argument\n");
        return false;
    }

    // check if list is empty
    if (list_empty(list)) {
        fprintf(stderr, "ERROR: list is empty; can't delete\n");
        return false;
    }

    // check if the first element is the one to delete
    if (memcmp(&list->arr[list->head], element, sizeof(TYPE)) == 0) {
        // store the old head
        int old_head = list->head;

        // update the head to the next element
        list->head = list->next[list->head];

        // add the removed index to holes
        list->holes[++list->hole_index] = old_head;
        list->list_len--;

        return true;
    }

    // check the rest of the list
    int curr = list->head;
    while (list->next[curr] != -1) {
        int next = list->next[curr];
        if (memcmp(&list->arr[next], element, sizeof(TYPE)) == 0) {
            // found the element to delete

            // link the current element to what the next was pointing to
            list->next[curr] = list->next[next];

            // add the removed index to holes
            list->holes[++list->hole_index] = next;
            list->list_len--;

            return true;
        }
        curr = next;
    }

    // element not found
    fprintf(stderr, "ERROR: element not found in list\n");
    return false;
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

    // check if list is empty
    if (list_empty(list)) {
        fprintf(stderr, "ERROR: list is empty; can't get element\n");
        return false;
    }

    // check if index is out of bounds
    if (index < 0 || index >= list->list_len) {
        fprintf(stderr, "ERROR: index out of bounds\n");
        return false;
    }

    // traverse the list to the specified index
    int curr = list->head;
    int traversed = 0;

    while (curr != -1) {
        if (traversed == index) {
            // found the element at the requested index
            memcpy(element, &list->arr[curr], sizeof(TYPE));
            return true;
        }

        traversed++;
        curr = list->next[curr];
    }

    // this should never be reached if the list structure is valid
    fprintf(stderr, "ERROR: list structure has been tampered with\n");
    return false;
}

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
    return list->head == -1;
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

    if (list->list_len >= MAX_LIST_LEN) {
        fprintf(stderr, "ERROR: list is full\n");
        return false;
    }

    // handle the case when list is empty
    if (list_empty(list)) {
        if (!index) {
            // list is empty
            list->head = 0;
            // list has its own copy of the element
            memcpy((void *) &list->arr[0], element, sizeof(TYPE)); // place element into the list
            list->next[0] = -1;
            list->list_len++;
            return true;
        } else {
            fprintf(stderr, "ERROR: can't insert at index %d; list is empty\n", index);
            return false;
        }
    }

    // list is non-empty but the index is out of bounds
    if (index > list->list_len && index < MAX_LIST_LEN) {
        fprintf(stderr, "ERROR: index out of bounds\n");
        return false;
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
                index_to_insert_at = list->list_len;
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

            list->list_len++;

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

    // index >= 1 from now onwards
    int curr = list->head;
    int traversed = 0;
    while (curr != -1) {
        if (traversed == index - 1) {
            // this is the element just before the one being removed
            const int next = list->next[curr];
            const int next_to_next = list->next[next];

            // set the current to point to the next element of the next element
            list->next[curr] = next_to_next;

            // we have created a hole; hole array can never be full
            list->holes[list->hole_index++] = next;
            return true;
        }

        traversed++;
        curr = list->next[curr];
    }

    // this should never be reached
    fprintf(stderr, "ERROR: list structure has been tampered with\n");
    return false;
}
