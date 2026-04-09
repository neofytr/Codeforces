#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        // next[r] is the min index n > k >= r such that arr[k] != arr[r]; it's -1 if it doesn't exist
        vector<int> next(n, -1);
        for (int r = n - 2; r >= 0; r--)
            if (arr[r] == arr[r + 1])
                next[r] = next[r + 1];
            else
                next[r] = r + 1;

        int q;
        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            if (next[l] == -1 || next[l] > r)
                cout << -1 << " " << -1 << endl;
            else
                cout << l + 1 << " " << next[l] + 1 << endl;
        }
        if (t)
            cout << endl;
    }
    return 0;
}
