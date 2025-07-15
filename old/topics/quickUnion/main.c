#include "quick_union.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t p, q;
    tree_t *tree = create_tree(10000);
    while (scanf("%zu %zu\n", &p, &q) == 2) {
        if (!find(tree, p, q)) {
            printf("NO\n");
            do_union(tree, p, q);
        } else {
            printf("YES\n");
        }
    }
    return EXIT_SUCCESS;
}
