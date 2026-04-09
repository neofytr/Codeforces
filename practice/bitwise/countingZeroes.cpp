#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long num;
    cin >> num;
    if (!num)
        return EXIT_SUCCESS;

    // we want to count the number of trailing zeroes in num
    cout << __builtin_popcount(num - 1) - (__builtin_popcount(num) - 1) << endl;
}