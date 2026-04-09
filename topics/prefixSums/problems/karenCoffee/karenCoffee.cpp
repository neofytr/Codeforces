#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: karenCoffee
// URL: https://codeforces.com/contest/816/problem/B
// Difficulty: hard
// Tags:
// Strategy:

#define MAX (200000 + 1)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, q;
    cin >> n >> k >> q;

    vector<int> update(MAX, 0);
    int l, r;
    for (int i = 0; i < n; i++) {
        cin >> l >> r;
        l--, r--;
        update[l] += 1;
        update[r + 1] -= 1;
    }

    for (int index = 1; index <= MAX; index++)
        update[index] += update[index - 1];
    vector<int> prefix(MAX, 0);
    for (int index = 1; index <= MAX; index++)
        prefix[index] = prefix[index - 1] + (update[index - 1] >= k ? 1 : 0);

    while (q--) {
        cin >> l >> r;
        l--, r--;
        cout << prefix[r + 1] - prefix[l] << endl;
    }
    return 0;
}