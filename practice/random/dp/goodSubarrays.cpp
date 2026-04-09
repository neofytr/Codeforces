#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    string str;
    cin >> str;

    vector<int> arr(n + 1), p(n + 1, 0);
    for (int r = 1; r <= n; r++)
        arr[r] = str[r - 1] - '0';
    for (int r = 1; r <= n; r++)
        p[r] += p[r - 1] + arr[r];

    int cnt = 0;
    unordered_map<int, int> f;
    f[p[0] - 0] = 1;
    for (int r = 1; r <= n; r++) {
        cnt += f[p[r] - r];
        f[p[r] - r]++;
    }

    cout << cnt << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}