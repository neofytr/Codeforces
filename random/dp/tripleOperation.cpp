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