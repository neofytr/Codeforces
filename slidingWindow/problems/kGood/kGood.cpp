#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: kGood
// URL: https://codeforces.com/contest/616/problem/D
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // subsegment monotonicity holds here
    unordered_set<int> s;
    unordered_map<int, int> freq;

    int leftMax, rightMax;
    int maxi = -1;
    int l = 0;
    for (int r = 0; r < n; r++) {
        if (!freq[arr[r]])
            s.insert(arr[r]);
        freq[arr[r]]++;
        while (l <= r && s.size() > k) {
            if (!(--freq[arr[l]]))
                s.erase(arr[l]);
            l++;
        }
        if (maxi < r - l + 1)
            leftMax = l + 1, rightMax = r + 1, maxi = r - l + 1;
    }
    cout << leftMax << " " << rightMax << endl;
    return 0;
}