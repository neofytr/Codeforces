#include "dequeue.h"

int main() {
    queue_t *queue = create_queue(10000);

    for (int counter = 0; counter < 100000; counter++) {
        for (int index = 0; index < 10000; index++) {
            push_back(queue, &index);
        }

        int element;
        for (int index = 0; index < 10000; index++) {
            pop_back(queue, &element);
        }
    }
}
