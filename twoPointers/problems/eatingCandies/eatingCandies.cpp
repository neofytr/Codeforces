#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: eatingCandies
// URL: https://codeforces.com/contest/1669/problem/F
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        int maxi = 0;
        int l = 0, r = n - 1;
        int sum = 0;
        while (l < r) {
            // alice eats a candy
            sum += arr[l];
            // bob compensates for it
            while (l <= r && sum - arr[r] >= 0)
                sum -= arr[r--];
            if (l <= r && !sum)
                maxi = max(maxi, l + 1 + n - r - 1);
            l++;
        }
        cout << maxi << endl;
    }
    return 0;
}