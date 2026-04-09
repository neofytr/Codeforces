#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        int val;
        vector<int> rem(m);
        for (int r = 1; r <= n; r++)
            cin >> val, rem[val % m]++;

        if (n == 1) {
            cout << 1 << endl;
            continue;
        }

        if (m == 1) {
            cout << 1 << endl;
            continue;
        }

        int cnt = 0;
        if (rem[0])
            cnt++;

        for (int r = 1; r <= m / 2; r++) {
            if (r == m - r) {
                if (rem[r])
                    cnt++;
            } else {
                int x = rem[r], y = rem[m - r];
                if (!x && !y)
                    continue;
                cnt++;
                cnt += max(0LL, abs(x - y) - 1);
            }
        }
        cout << cnt << endl;
    }
    return 0;
}