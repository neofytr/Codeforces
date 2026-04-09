#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: slidingWindowSum
// URL: https://cses.fi/problemset/task/3220
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    int x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<int> arr(n);
    arr[0] = x;
    for (int r = 1; r < n; r++)
        arr[r] = (a * arr[r - 1] + b) % c;

    int sum = 0;
    vector<int> windowSums;
    int l = 0;
    for (int r = 0; r < n; r++) {
        sum += arr[r];
        if (r - l + 1 == k)
            windowSums.push_back(sum), sum -= arr[l++];
    }

    int xr = 0;
    for (const int val : windowSums)
        xr = xr ^ val;
    cout << xr << endl;
    return 0;
}