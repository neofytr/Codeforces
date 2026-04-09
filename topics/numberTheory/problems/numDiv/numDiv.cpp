#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: numDiv
// URL: Not provided
// Difficulty: medium
// Tags:
// Strategy:

#define MAX 1000000
#define MOD (1000000000 + 7)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1 <= t <= 100000
    // 1 <= x <= 1000000

    // O(MAX * log(MAX)) preprocessing
    vector<int> smallestPrime(MAX + 1, -1);
    for (int r = 2; r <= MAX; r++)
        for (int j = r; j <= MAX; j += r)
            if (smallestPrime[j] == -1)
                smallestPrime[j] = r;

    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;

        // each test case is done in O(log(x))
        int cnt = 1;
        while (x != 1) {
            int sum = 1;
            const int p = smallestPrime[x];
            while (!(x % p))
                x /= p, sum++;
            cnt = (cnt * sum) % MOD;
        }
        cout << cnt << endl;
    }
    return 0;
}