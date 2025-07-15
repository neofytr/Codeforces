// https://codeforces.com/problemset/problem/1097/B
#include <bits/stdc++.h>
using namespace std;

bool isPowerOfTwo(long long n)
{
    return (n > 0) && !(n & (n - 1));
}

int main()
{
    long long n;
    cin >> n;

    vector<long long> arr(n);
    for (long long &val : arr)
        cin >> val;

    // 1 denotes clockwise rotation, 0 denotes anticlockwise rotation

    long long highest = 0;
    long long iter = 0;
    long long sum = accumulate(arr.begin(), arr.end(), 0); // starting with subset 0 (all anticlockwise)
    long long curr = sum;

    for (long long subset = 0; subset < (1LL << n); subset++)
    {
        if (isPowerOfTwo(subset))
        {
            curr = sum - 2 * arr[highest++];
            iter = 0;
        }
        else if (subset) // won't work if subset is zero
            curr -= 2 * arr[iter++];

        if (!(abs(curr) % 360)) // would ensure that the case when subset = 0 runs perfectly
        {
            cout << "YES\n";
            return EXIT_SUCCESS;
        }
    }

    cout << "NO\n";
    return EXIT_SUCCESS;
}