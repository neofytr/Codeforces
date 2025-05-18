#include <bits/stdc++.h>
using namespace std;

int main()
{
    double x, eps;
    cin >> x >> eps;

    // x > 1

    // we need to find sqrt(x) with some precision eps

    double left = 0;
    double right = x;
    double mid;

    // we maintain the invariant that
    // left < right
    // left * left < x
    // right * right >= x

    for (int counter = 0; counter < 100; counter++)
    {
        // usually, a 100 iterations do for any arbitrary precision
        mid = left + (right - left) / 2;
        if (mid * mid < x)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }

    cout << mid << endl;

    // for precision eps
    mid = -1;

    left = 0;
    right = x;

    while (right - left > eps)
    {
        mid = left + (right - left) / 2;
        if (mid * mid < x)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }

    cout << mid << endl;
    return EXIT_SUCCESS;
}