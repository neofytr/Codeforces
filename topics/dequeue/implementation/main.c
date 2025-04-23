#include "dequeue.h"

int main() {
    queue_t *queue = create_queue(1000);

    for (int counter = 0; counter < 1; counter++) {
        for (int index = 0; index < 1000; index++) {
            push_back(queue, &index);
        }

        int element;
        for (int index = 0; index < 1000; index++) {
            pop_back(queue, &element);
        }
    }
}
