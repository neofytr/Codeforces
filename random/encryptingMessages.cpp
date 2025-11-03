#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, m, c;
    cin >> n >> m >> c;

    vector<int> a(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> a[r];

    vector<int> pref(n + 2, 0);
    vector<int> b(m + 1);
    for (int r = 1; r <= m; r++)
        cin >> b[r];

    for (int r = 1; r <= m; r++) {
        int left = r;
        int right = n - m + r;
        pref[left] += b[r];
        pref[right + 1] -= b[r];
    }

    for (int r = 1; r <= n; r++)
        pref[r] = (pref[r] + pref[r - 1] + c) % c, a[r] = (a[r] + pref[r] + c) % c, cout << a[r] << " ";
    cout << endl;
    return 0;
}