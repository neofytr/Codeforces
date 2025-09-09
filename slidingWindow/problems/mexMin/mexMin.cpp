#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: mexMin
// URL: https://atcoder.jp/contests/abc194/tasks/abc194_e
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    set<int> mex;
    for (int r = 0; r <= n; r++)
        mex.insert(r);

    unordered_map<int, int> mp;
    int l = 0;
    int mini = LLONG_MAX;
    for (int r = 0; r < n; r++) {
        mp[arr[r]]++;
        if (mex.find(arr[r]) != mex.end())
            mex.erase(arr[r]);
        if (r - l + 1 == m) {
            mini = min(mini, *mex.begin());
            if (!(--mp[arr[l]]))
                mex.insert(arr[l]);
            l++;
        }
    }
    cout << mini << endl;
    return 0;
}