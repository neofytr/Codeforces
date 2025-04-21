#include "max_heap.h"

#define DEFAULT_SIZE 1024
max_heap_t *max_heap_create()
{
    int default_val = -1; // signifies no element is there
    dyn_arr_t *arr = dyn_arr_create(DEFAULT_SIZE, sizeof(int), &default_val);
    if (!arr)
    {
        fprintf(stderr, "ERROR: max heap creation failed: %s\n", strerror(errno));
        return NULL;
    }

    return arr;
}

bool max_heap_insert(max_heap_t *max_heap, int element)
{
    if (!max_heap)
    {
        fprintf(stderr, "ERROR: invalid max heap argument\n");
        return false;
    }

    // insert element at the end and bubble up
    dyn_arr_append(max_heap, &element); // inserting at the end doesn't make the binary tree incomplete

    size_t new_element_index = max_heap->last_index;
    if (!new_element_index)
    {
        return true;
    }

    int parent;
    size_t parent_index = (new_element_index - 1) / 2;
    dyn_arr_get(max_heap, parent_index, &parent);

    while (parent <= element)
    {
        // swap if the parent is less equal to the element being inserted
        dyn_arr_set(max_heap, parent_index, element);
        dyn_arr_set(max_heap, new_element_index, parent);

        new_element_index = parent_index;
        if (!new_element_index)
        {
            return true;
        }
        parent_index = (new_element_index - 1) / 2;
        dyn_arr_get(max_heap, parent_index, &parent);
    }

    return true;
}

bool max_heap_delete(max_heap_t *max_heap, int *element)
{
    if (!max_heap)
    {
        fprintf(stderr, "ERROR: invalid max heap argument\n");
        return false;
    }

    if (max_heap->is_empty)
    {
        fprintf(stderr, "ERROR: max heap is empty; can't delete\n");
        return false;
    }

    if (max_heap->len == 1)
    {
        if (!dyn_arr_get(max_heap, 0, element))
        {
            fprintf(stderr, "ERROR: could not get root element\n");
            return false;
        }
        dyn_arr_pop(max_heap, NULL); // remove the only element

        return true;
    }

    // swap the root node with the last element in the array
    // pop the last element (doesn't make the max heap incomplete)
    // then bubble down

    int root;
    int last;

    // swap
    dyn_arr_get(max_heap, 0, &root);
    dyn_arr_get(max_heap, max_heap->last_index, &last);

    dyn_arr_set(max_heap, 0, last);
    dyn_arr_set(max_heap, max_heap->last_index, root);

    // pop the last element storing it in element
    dyn_arr_pop(max_heap, element);

    // bubble down
    size_t index = 0;

    while (1)
    {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;

        int current, left_val = -1, right_val = -1;
        dyn_arr_get(max_heap, index, &current);
        dyn_arr_get(max_heap, left, &left_val);
        dyn_arr_get(max_heap, right, &right_val);

        // stop if no children
        if (left_val == -1 && right_val == -1)
            break;

        size_t max_child_index;
        int max_child_val;

        if (left_val > right_val)
        {
            max_child_index = left;
            max_child_val = left_val;
        }
        else
        {
            max_child_index = right;
            max_child_val = right_val;
        }

        if (max_child_val > current)
        {
            // swap
            dyn_arr_set(max_heap, index, max_child_val);
            dyn_arr_set(max_heap, max_child_index, current);
            index = max_child_index;
        }
        else
        {
            break;
        }
    }

    return true;
}