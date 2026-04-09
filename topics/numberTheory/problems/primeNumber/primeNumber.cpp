#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: primeNumber
// URL: https://codeforces.com/contest/359/problem/C
// Difficulty: hard
// Tags:
// Strategy:

#define MOD 1000000007

int pw(const int a, const int b) {
    if (!b)
        return 1;
    const int r = pw(a, b / 2);
    if (b & 1)
        return (((r * r) % MOD) * a) % MOD;
    return (r * r) % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;

    vector<int> arr(n);
    int s = 0;
    for (int &val : arr)
        cin >> val, s += val;
    // arr is non-decreasing

    unordered_map<int, int> mp;
    for (int r = 0; r < n; r++)
        mp[s - arr[r]]++;

    int curr = s - arr[n - 1]; // this is the minimum power
    while (!(mp[curr] % x)) {
        mp[curr + 1] += mp[curr] / x;
        mp[curr] = 0;
        curr++;
    }

    cout << pw(x, curr) << endl;

    return 0;
}