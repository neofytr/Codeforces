#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)
#define MAX_PW (12)

int pw[MAX_PW + 1];
int cnt[MAX + 1];

int f_cnt(const int x) {
    int left = 0;
    int right = MAX_PW;

    while (right != left + 1) {
        if (const int mid = left + (right - left) / 2; pw[mid] <= x)
            left = mid;
        else
            right = mid;
    }

    return left + 1;
}

void solve() {
    int l, r;
    cin >> l >> r;

    int res = min(cnt[l] + cnt[l + 1] + cnt[l], cnt[l + 1] + cnt[l] + cnt[l + 1]);
    if (r <= l + 1) {
        cout << res << endl;
        return;
    }

    int i = l + 2;
    int p = (cnt[l + 2] - 1) + 1;
    while (true) {
        if (pw[p] > r) {
            res += (r - i + 1) * cnt[i];
            break;
        }

        res += (pw[p] - i) * cnt[i];
        i = pw[p++];
    }

    cout << res << endl;
}

int32_t main() {
    int t;
    cin >> t;

    pw[0] = 1;
    for (int r = 1; r <= MAX_PW; r++)
        pw[r] = pw[r - 1] * 3;

    for (int r = 1; r <= MAX; r++)
        cnt[r] = f_cnt(r);

    while (t--) {
        solve();
    }
    return 0;
}