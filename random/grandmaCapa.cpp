#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    string str;
    cin >> str;

    int mini = LLONG_MAX;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        int l = 0, r = n - 1;
        int cnt = 0;
        bool psbl = true;
        while (l < r) {
            if (str[l] == str[r]) {
                l++, r--;
                continue;
            }

            if (str[l] != ch && str[r] != ch) {
                psbl = false;
                break;
            }

            if (str[l] == ch)
                l++, cnt++;
            if (str[r] == ch)
                r--, cnt++;
        }
        if (psbl)
            mini = min(mini, cnt);
    }

    if (mini == LLONG_MAX) {
        cout << -1 << endl;
        return;
    }
    cout << mini << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}