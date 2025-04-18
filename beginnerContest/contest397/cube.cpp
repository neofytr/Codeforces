#include <bits/stdc++.h>
using namespace std;

int main()
{
    uint64_t n;
    cin >> n;

    uint64_t delta = 1;
    uint64_t cube = delta * delta * delta;
    while (cube < n)
    {
        if ((n - cube) % delta)
        {
            delta++;
            cube = delta * delta * delta;
            continue;
        }

        if (((n - cube) / delta) % 3)
        {
            delta++;
            cube = delta * delta * delta;
            continue;
        }

        uint64_t prod = ((n - cube) / delta) / 3;
        uint64_t x = prod, y;

        while (x >= 1)
        {
            if (prod % x)
            {
                x--;
                continue;
            }

            y = prod / x;
            if (x >= y && x - y == delta)
            {
                cout << x << " " << y << endl;
                return EXIT_SUCCESS;
            }
            x--;
        }

        delta++;
        cube = delta * delta * delta;
    }

    cout << -1 << endl;
    return EXIT_SUCCESS;
}