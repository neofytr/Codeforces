#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }

    int *arr = malloc(n * sizeof(int));
    if (!arr)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int target;
    printf("Enter the target sum: ");
    scanf("%d", &target);

    bool found = false;
    for (long subset = 1; subset < (1L << n); subset++)
    {
        int sum = 0;
        bool exceededTarget = false;

        for (int i = 0; i < n; i++)
        {
            if ((1L << i) & subset)
            {
                sum += arr[i];
                if (sum > target)
                {
                    exceededTarget = true;
                    break;
                }
            }
        }

        if (!exceededTarget && sum == target)
        {
            found = true;
            printf("\nFound subset with sum %d:\n", target);
            for (int i = 0; i < n; i++)
            {
                if ((1L << i) & subset)
                {
                    printf("%d ", arr[i]);
                }
            }
            printf("\n");
        }
    }

    if (!found)
    {
        printf("No subset found with sum equal to %d\n", target);
    }

    free(arr);
    return 0;
}