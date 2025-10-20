#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    string a, b;
    cin >> a >> b;

    vector<int> z(n + 1, 0), o(n + 1, 0);
    for (int r = 1; r <= n; r++) {
        z[r] += z[r - 1] + (a[r - 1] == '0' ? 1 : 0);
        o[r] += o[r - 1] + (a[r - 1] == '1' ? 1 : 0);
    }

    if (n == 1 && a == b) {
        cout << "YES\n";
        return;
    }

    if (n == 1 && a != b) {
        cout << "NO\n";
        return;
    }

    int i = n - 1, j;
    while (i >= 0) {
        j = i;
        if (!i) {
            cout << "NO\n";
            return;
        }

        if (a[i] != b[i]) {
            while (j >= 1 && a[j - 1] != b[j - 1])
                j--;

            if (z[i + 1] != o[i + 1]) {
                cout << "NO\n";
                return;
            }
        } else {
            while (j >= 1 && a[j - 1] == b[j - 1])
                j--;

            if (i != n - 1 && z[i + 1] != o[i + 1]) {
                cout << "NO\n";
                return;
            }
        }
        i = j - 1;
    }
    cout << "YES\n";
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}