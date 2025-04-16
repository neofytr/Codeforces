#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    vector<long long> prefix(n + 1, 0);
    vector<long long> suffix(n + 1, 0);

    for (int index = 1; index <= n; index++)
    {
        prefix[index] = __gcd(prefix[index - 1], arr[index - 1]);
    }

    for (int index = n - 1; index >= 0; index--)
    {
        suffix[index] = __gcd(suffix[index + 1], arr[index]);
    }

    long long gcdWithout;
    long long maxgcd = __gcd(prefix[0], suffix[1]);

    for (int index = 0; index < n; index++)
    {
        gcdWithout = __gcd(prefix[index], suffix[index + 1]);
        maxgcd = max(maxgcd, gcdWithout);
    }

    cout << maxgcd << endl;

    return 0;
}
