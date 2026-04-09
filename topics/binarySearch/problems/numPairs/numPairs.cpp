#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: numPairs
// URL: https://codeforces.com/problemset/problem/1538/C
// Difficulty: medium
// Tags:
// Strategy:

int count(vector<int> &arr, int bound) {
    // we want to count the number of pairs (i, j) where 0 <= i < j < n such that arr[i] + arr[j] <= bound
    int cnt = 0;
    int n = arr.size();

    for (int left = 0; left < n; left++) {
        int target = bound - arr[left];
        // search only in the range [left+1, end)
        auto itr = upper_bound(arr.begin() + left + 1, arr.end(), target);
        int index = itr - arr.begin();
        cnt += (index - (left + 1));
    }

    return cnt;
}

void solve() {
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    sort(arr.begin(), arr.end());
    // we are to find the number of pairs (i, j) such that 0 <= i < j < n where l <= arr[i] + arr[j] <= r
    // we count the number of pairs with sum <= r and then subtract the pairs with sum < l

    cout << count(arr, r) - count(arr, l - 1) << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}