#include <iostream>
#include <vector>
using namespace std;

long long solve(long long x, long long y)
{
    long long xor_val = x ^ y;

    // if x == y, the sequences would be identical, but the problem states x != y
    // so xor_val is guaranteed to be non-zero

    // find the position of the least significant set bit in xor_val
    long long result = 1;
    while (!(xor_val & 1))
    {
        result *= 2;
        xor_val >>= 1;
    }

    return result;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        long long x, y;
        cin >> x >> y;

        cout << solve(x, y) << endl;
    }

    return 0;
}