#include <bits/stdc++.h>
using namespace std;

#define int long long

#define MAX (int)(2 * 1e5 + 1)
int tmp[MAX + 1];
int cnt[MAX + 1];

int32_t main() {
    int n, k, q;
    cin >> n >> k >> q;

    int l, r;
    while (n--) {
        cin >> l >> r;
        tmp[l] += 1;
        tmp[r + 1] -= 1;
    }

    for (int r = 1; r <= MAX; r++)
        tmp[r] += tmp[r - 1], cnt[r] += cnt[r - 1] + (tmp[r] >= k ? 1 : 0);

    int a, b;
    while (q--) {
        cin >> a >> b;
        cout << cnt[b] - cnt[a - 1] << endl;
    }
    return 0;
}