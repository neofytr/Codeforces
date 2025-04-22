#include "./linked_list.h"

int main() {
    list_t *list = list_create(100000);

    for (int index = 0; index < 50; index++) {
        for (int counter = 0; counter < 10000; counter++) {
            list_insert(list, counter, &counter);
        }

        int element;
        for (int counter = 0; counter < 10000; counter++) {
            list_pop(list, &element);
        }
    }

    return EXIT_SUCCESS;
}
