#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t, a, b;
    scanf("%d\n", &t);

    while (t--)
    {
        scanf("%d %d\n", &a, &b);

        // operate
    }

    int a, b;

    // stop when both a and b are zero
    while (scanf("%d %d\n", &a, &b), a || b)
    {
        // operate
    }

    int a, b;

    // stop when EOF reached

    while (scanf("%d %d\n", &a, &b) != EOF)
    {
        // operate
    }

    int a, b;

    // print blank line after each test case (except the last) and label the case no
    // terminated by EOF

    int count = 0;
    while (scanf("%d %d\n", &a, &b) != EOF)
    {
        if (count)
        {
            printf("\n");
        }
        printf("case %d: %d\n", count++, a + b);
    }

    int k;
    while (scanf("%d ", &k) != EOF) // a single space matches any number of whitespace characters
    {
        int ans = 0, temp;
        while (k--)
        {
            scanf("%d ", &temp);
            ans += temp;
        }

        printf("%d\n", ans);
    }

    // we are not given the integer k at the beginning

    while (true)
    {
        int ans = 0, v;
        char dummy;

        while (scanf("%d%c", &v, &dummy) != EOF)
        {
            ans += v;
            if (dummy == '\n')
            {
                break;
            }
        }

        printf("%d\n", ans);

        // even if we have detected an EOF by a scanf call, any number of scanf calls
        // after it will return the EOF
        if (feof(stdin))
            break; // test EOF
    }

    return 0;
}