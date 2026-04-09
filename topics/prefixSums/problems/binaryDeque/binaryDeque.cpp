#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: binaryDeque
// URL: https://codeforces.com/problemset/problem/1692/E
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;
        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;
        // we want the maximum length segment [l, r] such that it's sum is == s
        // we want the maximum length segment [l, r] such that its sum <= s
        // this maximum length segment will either have sum s, or there is no segment which has sum s

        // subsegment monotonic
        int l = 0;
        int sum = 0;
        int maxi = -1;
        for (int r = 0; r < n; r++) {
            sum += arr[r];
            while (l <= r && sum > s)
                sum -= arr[l++];
            if (l <= r && sum == s)
                maxi = max(maxi, r - l + 1);
        }

        if (maxi == -1) {
            cout << -1 << endl;
            continue;
        }
        cout << n - maxi << endl;
    }
    return 0;
}