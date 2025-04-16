#include <bits/stdc++.h>
using namespace std;

long long int_pow(long long base, int exponent)
{
    long long result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result *= base;
        base *= base;
        exponent /= 2;
    }
    return result;
}

int main()
{
    int n, m;
    cin >> n >> m;

    if (n == 1)
    {
        cout << m + 1 << endl;
        return EXIT_SUCCESS;
    }

    long long x = (int_pow(n, m + 1) - 1) / (n - 1);
    if (x > 1000000000)
    {
        cout << "inf\n";
        return EXIT_SUCCESS;
    }

    cout << x << endl;
}