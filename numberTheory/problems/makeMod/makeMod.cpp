#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

// Problem: makeMod
// URL: https://codeforces.com/problemset/problem/1909/B
// Difficulty: medium
// Tags:
// Strategy:

int solve(const int n) {
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // f(k) = number of distinct values in the multiset {arr[r] % k, 0 <= r < n}

    // If f(k) = 1, then f(2k) = 1 or 2
    // Proof ->
    // Let f(k) = 1 for some k
    // Thus, arr[r] % k = w for all 0 <= r < n
    // arr[r] = k * q[r] + w for all 0 <= r < n
    // Now, if q[r] is even, then
    // arr[r] = (2k) * g[r] + w -> arr[r] % (2k) = w
    // Otherwise, if q[r] is odd, then
    // arr[r] = k * (2 * g[r] + 1) + w -> arr[r] = (2k) * g[r] + (w + k)
    // Thus, arr[r] % 2k = (w + k) since 0 <= w + k < 2k
    // Thus, f(2k) = 1 or 2

    // If there are n, m such that n != m and arr[n] % 2 = 1 and arr[m] % 2 = 0, then answer is 2
    // If arr[r] % 2 = 1 for all 0 <= r < n or arr[r] % 2 = 0 for all 0 <= r < n, f(k) = 1, and we use
    // the above theorem to find h such that f(h) = 2

    // Let j be such that 2^j > max(arr[r], 0 <= r < n)
    // Then f(2^j) = n >= 2
    // Also, f(2) = 1
    // Then, there must exist some t such that 1 < t <= j such that f(t) = 2
    // Suppose, there is none. Then we can prove via induction that f(2^r) = 1 for all 1 <= r <= j
    // This is a contradiction since f(2^j) = n >= 2
    // Thus, there is some 1 < t <= j such that f(t) = 2

    for (int k = 1; k <= (1e18); k <<= 1) {
        set<int> rem;
        for (const int val : arr)
            rem.insert(val % k);
        if (rem.size() == 2)
            return k;
    }
    return -1; // will never reach here
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, n;
    cin >> t;
    while (t--)
        cin >> n, cout << solve(n) << endl;
    return 0;
}