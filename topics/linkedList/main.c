#include "./linked_list.h"

int main() {
    list_t *list = list_create();

    for (int index = 0; index < 100000; index++) {
        list_insert(list, index, &index);
    }

    for (int index = 0; index < 10; index++) {
        int element;
        list_get(list, index, &element);
        fprintf(stdout, "%d => %d\n", index, element);
    }

    return EXIT_SUCCESS;
}
