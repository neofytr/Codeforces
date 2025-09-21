#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: sherlock
// URL: https://codeforces.com/problemset/problem/776/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<bool> isPrime(n + 2, true);
    vector<int> primes;
    for (int r = 2; r * r <= n + 1; r++)
        if (isPrime[r]) {
            primes.push_back(r);
            for (int j = r * r; j <= n + 1; j += r)
                isPrime[j] = false;
        }

    if (primes.empty()) {
        cout << 1 << endl;
        for (int r = 2; r <= n + 1; r++)
            cout << 1 << " ";
        cout << endl;
    } else {
        cout << 2 << endl;
        vector<int> div(n + 2, false);
        for (const int p : primes)
            for (int r = 2 * p; r <= n + 1; r += p)
                div[r] = true;

        for (int r = 2; r <= n + 1; r++)
            if (isPrime[r])
                cout << 1 << " ";
            else if (div[r])
                cout << 2 << " ";
            else
                cout << 1 << " ";
        cout << endl;
    }

    return 0;
}