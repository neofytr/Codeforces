#include <stdio.h>

int main() {
    size_t t, a, b;
    scanf("%zu", &t);
    
    while (t--) {
        scanf("%zu %zu", &a, &b);
        size_t remainder = a % b;
        printf("%zu\n", (remainder == 0) ? 0 : (b - remainder));
    }

    return 0;
}
