#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: karenAndCoffee
// URL: https://codeforces.com/contest/816/problem/B
// Difficulty: medium
// Tags:
// Strategy:

#define MAX_TEMP (200000)
int temp[MAX_TEMP + 1], cnt[MAX_TEMP + 2];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, q;
    cin >> n >> k >> q;

    int l, rt;
    while (n--) {
        cin >> l >> rt;
        temp[l] += 1;
        temp[rt + 1] += -1;
    }

    for (int r = 1; r <= MAX_TEMP; r++)
        temp[r] += temp[r - 1];

    for (int r = 1; r <= MAX_TEMP + 1; r++)
        cnt[r] = cnt[r - 1] + (temp[r - 1] >= k ? 1 : 0);

    int a, b;
    while (q--) {
        cin >> a >> b;
        cout << cnt[b + 1] - cnt[a] << endl;
    }
    return 0;
}