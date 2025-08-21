#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: numPairs
// URL: https://codeforces.com/problemset/problem/1538/C
// Difficulty: easy
// Tags:
// Strategy:

int count(int bound, vector<int> &arr) {
    int n = (int)arr.size();
    int count = 0;
    // we are to find the number of pairs (i, j) where i < j such that a[i] + a[j] <= bound
    for (int i = 0; i < n; i++) {
        // a[j] <= bound - a[i]
        int target = bound - arr[i];
        auto itr = upper_bound(arr.begin() + i + 1, arr.end(), target);
        int index = itr - arr.begin() - 1;
        count += (index - i);
    }
    return count;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, l, r;
        cin >> n >> l >> r;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;
        // we are to find the number of pairs (i, j) where 0 <= i < j < n where the sum of a[i] + a[j] >= l and <= r

        // we find the number of pairs with sum <= r and then subtract from it the num of pairs <= l - 1
        sort(arr.begin(), arr.end());
        cout << count(r, arr) - count(l - 1, arr) << endl;
    }
    return 0;
}