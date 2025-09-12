#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: tprimes
// URL: https://codeforces.com/problemset/problem/230/B
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

    vector<int> primes(1000000 + 1, true);
    for (int r = 2; r <= 1000000; r++)
        if (primes[r]) {
            for (int j = 2 * r; j <= 1000000; j += r)
                primes[j] = false;
        }

    for (const int val : arr) {
        if (val == 1) {
            cout << "NO\n";
            continue;
        }
        const int sq = sqrt(val);
        if (sq * sq != val) {
            cout << "NO\n";
            continue;
        }
        if (primes[sq])
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}