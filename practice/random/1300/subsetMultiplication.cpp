#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> b(n + 1);
    for (int r = 1; r <= n; r++) cin >> b[r];

    int cnt = 0;
    unordered_map<int, int> f;
    for (int r = 1; r <= n - 1; r++)
        if (b[r + 1] % b[r]) {
            cnt++;
            for (int i = 1; i * i <= b[r]; i++) {
                int one = i, two = b[r] / i;
                if (!(b[r + 1] % (b[r] / one)))
                    f[one]++;
                if (one != two && !(b[r + 1] % (b[r] / two)))
                    f[two]++;
            }
        }

    for (auto &[val, c] : f)
        if (c == cnt) {
            cout << val << endl;
            return;
        }
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}