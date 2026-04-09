#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: omkar
// URL: https://codeforces.com/problemset/problem/1372/B
// Difficulty: medium
// Tags:
// Strategy:

int gcd(const int a, const int b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int mini = LLONG_MAX;
        for (int r = 1; r * r <= n; r++) {
            if (!(n % r)) {
                int divOne = r;
                int divTwo = n / r;

                if (n - r >= 1)
                    mini = min(mini, n - r);
                if (n - n / r >= 1)
                    mini = min(mini, n - n / r);
            }
        }
        cout << mini << " " << n - mini << endl;
    }

    return 0;
}