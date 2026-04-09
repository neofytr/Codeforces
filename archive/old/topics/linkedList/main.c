#include "./linked_list.h"

int main() {
    list_t *list = list_create(10000);

    for (int index = 0; index < 56; index++) {
        for (int counter = 0; counter < 10000; counter++) {
            list_insert(list, counter, &counter);
        }

        int element;
        for (int counter = 0; counter < 10000; counter++) {
            list_pop(list, &element);
        }
        printf("END index -> %d\n", index);
    }

    return EXIT_SUCCESS;
}
