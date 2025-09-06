#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are given q queries of the form (l, r, x), which means increment each of arr[l], ..., arr[r] by x, where 0 <= l <= r < n
    int q, l, r, x;
    cin >> q;
    vector<int> prefix(n + 1);
    while (q--) {
        cin >> l >> r >> x;
        prefix[l] += x;
        prefix[r + 1] -= x;
    }

    arr[0] += prefix[0];
    for (int r = 1; r <= n; r++)
        prefix[r] += prefix[r - 1], arr[r] += prefix[r];
}