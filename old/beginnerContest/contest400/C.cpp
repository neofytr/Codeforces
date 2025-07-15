#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    set<long long> good_numbers;

    for (long long b = 1; b * b <= n; b++)
    {
        long long b_squared = b * b;

        for (long long a = 1, power = 2; power * b_squared <= n; a++, power *= 2)
        {
            good_numbers.insert(power * b_squared);
        }
    }

    cout << good_numbers.size() << endl;
    return 0;
}