#include <bitset>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const size_t MAX_TOPIC = 4 * 10 * 10 * 10;

int main()
{
    bitset<MAX_TOPIC + 1> topics;  // no need to initialize to 0, bitset default constructor does this
    size_t n, m, q;
    size_t l_one, r_one;
    size_t l_two, r_two;

    scanf("%zu %zu %zu", &n, &m, &q);

    int *a = (int *)malloc(sizeof(int) * n);
    if (!a)
    {
        return EXIT_FAILURE;
    }

    int *b = (int *)malloc(sizeof(int) * m);
    if (!b)
    {
        free(a);  
        return EXIT_FAILURE;
    }

    for (size_t counter = 0; counter < n; counter++)
    {
        scanf("%d", &a[counter]);
    }

    for (size_t counter = 0; counter < m; counter++)
    {
        scanf("%d", &b[counter]);
    }

    for (size_t counter = 0; counter < q; counter++)
    {
        scanf("%zu %zu %zu %zu", &l_one, &r_one, &l_two, &r_two);
        
        for (size_t index = l_one - 1; index < r_one; index++)
        {
            topics[a[index]] = topics[a[index]] ^ 1;
        }

        for (size_t index = l_two - 1; index < r_two; index++)
        {
            topics[b[index]] = topics[b[index]] ^ 1;
        }

        printf("%zu\n", topics.count());
        topics.reset();  
    }

    free(a);
    free(b);

    return EXIT_SUCCESS;
}