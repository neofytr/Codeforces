#include <bits/stdc++.h>
using namespace std;

// calculate factorial(n) by doing 1 * 2 * 3 * ... * n

int factorial(int n) {
    // this is reverse traversal
    // recurse before use for reverse traversal
    // recurse after use for order traversal
    if (n == 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

// traversing linked list in reverse order using recursion

typedef struct link {
    struct link *next;
    int data;
} link_t;

void link_traverseR(link_t *link, void (*visit)(link_t *)) {
    // recurse before use for reverse traversal
    if (!link) {
        return;
    }

    link_traverseR(link->next, visit);
    visit(link);
}

// traversing an array in reverse order

void traverseR(int *arr, int len) {
    if (len == 0) {
        return;
    }

    traverseR(arr + 1, len - 1); // go deeper first
    printf("%d\n", *arr); // print after unwinding
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int *ptr = arr;
    traverseR(ptr, 6);

    return EXIT_SUCCESS;
}
