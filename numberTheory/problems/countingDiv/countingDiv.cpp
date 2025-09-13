#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: countingDiv
// URL: https://cses.fi/problemset/task/1713
// Difficulty: easy
// Tags:
// Strategy:

#define MAX (1000000)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> maxPrime(MAX + 1, -1);
    for (int r = 2; r <= MAX; r++)
        if (maxPrime[r] == -1)
            for (int j = r; j <= MAX; j += r)
                maxPrime[j] = r;

    int x;
    while (n--) {
        cin >> x;
        int cnt = 1;

        while (x != 1) {
            int sum = 1;
            const int p = maxPrime[x];
            while (!(x % p))
                sum++, x /= p;
            cnt *= sum;
        }
        cout << cnt << endl;
    }
    return 0;
}