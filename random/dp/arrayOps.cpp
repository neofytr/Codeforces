#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int cnt[MAX + 1];

void solve() {
    int n, k;
    cin >> n >> k;

    for (int r = 1; r <= MAX; r++)
        cnt[r] = 0;

    int v;
    for (int r = 1; r <= n; r++)
        cin >> v, cnt[v]++;

    int i = 1, j = 1;
    while (k) {
        j = i + 1;
        while (cnt[i] && k) {
            int one = cnt[i], two = cnt[j], three = k;
            cnt[j] -= min(one, min(two, three));
            cnt[i] -= min(one, min(two, three));
            k -= min(one, min(two, three));
            if (!cnt[j])
                j++;
        }
        i = j;
    }
}

int32_t main() {
    int t;

    while (t--) {
        solve();
    }
    return 0;
}