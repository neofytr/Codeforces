#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: rangeUpdate
// URL: Not provided
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

    vector<int> update(n + 1, 0);
    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x; // l,r are 0-based indexes
        update[l] += x;
        update[r + 1] -= x;
    }

    // propagate all updates and finally update the real array
    arr[0] += update[0];
    for (int index = 1; index < n; index++) {
        update[index] += update[index - 1];
        arr[index] += update[index];
    }

    for (const int val : arr)
        cout << val << " ";
    cout << endl;
    return 0;
}