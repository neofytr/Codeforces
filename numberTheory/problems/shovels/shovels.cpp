#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: shovels
// URL: medium
// Difficulty: https://codeforces.com/problemset/problem/1360/D
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        int maxi = 1;
        for (int r = 1; r * r <= n; r++) {
            if (!(n % r)) {
                int divOne = r;
                int divTwo = n / r;
                if (divOne <= k)
                    maxi = max(divOne, maxi);
                if (divTwo <= k)
                    maxi = max(divTwo, maxi);
            }
        }
        cout << n / maxi << endl;
    }

    return 0;
}