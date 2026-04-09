#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: staticRangeSum
// URL: https://cses.fi/problemset/task/1646
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> prefix(n + 1, 0);
    for (int index = 1; index <= n; index++)
        prefix[index] = prefix[index - 1] + arr[index - 1];

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << prefix[b + 1] - prefix[a] << endl;
    }
    return 0;
}