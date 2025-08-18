#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: totalLength
// URL: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    cin >> n >> s;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int sum = 0;
    int ans = 0;
    // segment [l, r] is good iff sum[l, r] <= s
    for (int r = 0, l = 0; r < n; r++) {
        // insert arr[r] into the segment
        sum += arr[r];
        while (l <= r && sum > s)
            sum -= arr[l++];
        if (l <= r) {
            // now, all the segments [k, r] where l <= k <= r are good
            // sum from 1 to (r - l + 1)
            ans += (r - l + 1) * (r - l + 2) / 2;
        }
    }
    cout << ans << endl;
    return 0;
}