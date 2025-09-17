#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

// Problem: GCDQ
// URL: https://vjudge.net/problem/CodeChef-GCDQ
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> arr(n + 1);
        for (int r = 1; r <= n; r++)
            cin >> arr[r];

        // pref[r] is the GCD of indexes [1, r]
        // suff[r] is the GCD of indexes [r, n]
        vector<int> pref(n + 1, 0);
        vector<int> suff(n + 1, 0);

        pref[1] = arr[1];
        for (int r = 2; r <= n; r++)
            pref[r] = gcd(pref[r - 1], arr[r]);
        suff[n] = arr[n];
        for (int r = n - 1; r >= 1; r--)
            suff[r] = gcd(suff[r + 1], arr[r]);

        while (q--) {
            int l, r;
            cin >> l >> r;

            if (l == 1) {
                // r < n
                cout << suff[r + 1] << endl;
            } else if (r == n) {
                // l > 1
                cout << pref[l - 1] << endl;
            } else {
                cout << gcd(pref[l - 1], suff[r + 1]) << endl;
            }
        }
    }

    return 0;
}