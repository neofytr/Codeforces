// https://codeforces.com/problemset/problem/1097/B
#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, curr;
    cin >> n;

    vector<long long> arr(n);
    for (long long &val : arr)
        cin >> val;

    // 1 denotes clockwise rotation, 0 denotes anticlockwise rotation
    for (long long subset = 0; subset < (1LL << n); subset++)
    {
        curr = 0;
        for (long long bit = 0; bit < n; bit++)
        {
            if (subset & (1LL << bit))
                curr += -arr[bit];
            else
                curr += arr[bit];
        }

        if (!(abs(curr) % 360))
        {
            cout << "YES\n";
            return EXIT_SUCCESS;
        }
    }

    cout << "NO\n";
    return EXIT_SUCCESS;
}