#include <bits/stdc++.h>
using namespace std;

int main()
{
    size_t x;
    cin >> x;

    // we need to check wheter x is a square or not

    if (x == 0 || x == 1 || x == 4) // check all cases less than equal to 4
    {
        cout << "YES" << endl;
        return EXIT_SUCCESS;
    }
    else if (x == 2 || x == 3)
    {
        cout << "NO" << endl;
        return EXIT_SUCCESS;
    }

    // now the square of any number n will necessarily be less than n / 2

    size_t left = 0;
    size_t right = x / 2 - 1;
    size_t mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (mid * mid > x)
        {
            right = mid - 1;
        }
        else if (mid * mid < x)
        {
            left = mid + 1;
        }
        else
        {
            cout << "YES" << endl;
            return EXIT_SUCCESS;
        }
    }

    cout << "NO" << endl;
    return EXIT_SUCCESS;
}