#include "linked_list.h"

int main() {
    list_t *list = list_create();

    for (int index = 0; index < 10000; index++) {
        list_append(list, &index);
    }

    int index, element;
    LIST_FOREACH(list, &index, &element) {
        printf("%d -> %d\n", index, element);
    }

    return EXIT_SUCCESS;
}
