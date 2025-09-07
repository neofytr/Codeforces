#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: approximating
// URL: https://codeforces.com/contest/602/problem/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int l = 0;
    multiset<int> m;
    int maxi = LLONG_MIN;
    for (int r = 0; r < n; r++) {
        m.insert(arr[r]);
        while (l <= r && *m.rbegin() - *m.begin() > 1)
            m.erase(m.find(arr[l])), l++;
        if (r >= l)
            maxi = max(maxi, r - l + 1);
    }
    cout << maxi << endl;
    return 0;
}