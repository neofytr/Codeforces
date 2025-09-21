#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: restoration
// URL: https://codeforces.com/problemset/problem/1409/C
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;

        int bestMax = LLONG_MAX;
        int bestA = -1, bestD = -1;

        for (int a = 1; a <= x; a++) {
            int num = y - a;
            if (num <= 0)
                continue; // y must be larger than a

            for (int d = 1; d * d <= num; d++) {
                if (num % d)
                    continue;

                // divisor d1
                int d1 = d;
                int len1 = num / d1 + 1; // length of sequence from a to y with step d1
                if ((x - a) % d1 == 0 && len1 <= n) {
                    int mx = a + (n - 1) * d1;
                    if (mx < bestMax) {
                        bestMax = mx;
                        bestA = a;
                        bestD = d1;
                    }
                }

                // divisor d2
                int d2 = num / d;
                int len2 = num / d2 + 1;
                if ((x - a) % d2 == 0 && len2 <= n) {
                    int mx = a + (n - 1) * d2;
                    if (mx < bestMax) {
                        bestMax = mx;
                        bestA = a;
                        bestD = d2;
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            cout << bestA + i * bestD << (i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}
