#include <bits/stdc++.h>
using namespace std;

void solve() {
    int m;
    cin >> m;
    vector<long long> arr(m);
    long long sum0 = 0;
    for (int j = 0; j < m; ++j) {
        cin >> arr[j];
        if ((j + 1) % 2 != 0) {
            sum0 += arr[j];
        } else {
            sum0 -= arr[j];
        }
    }

    long long best = 0;

    if (m > 1) {
        best = max(best, (long long)m - (m % 2 == 0 ? 2 : 1));
    }

    long long mini = LLONG_MAX;
    for (int j = 1; j <= m; ++j) {
        if (j % 2 != 0) {
            long long temp = j + 2 * arr[j - 1];
            mini = min(mini, temp);
        } else {
            if (mini != LLONG_MAX) {
                long long temp = j + 2 * arr[j - 1];
                best = max(best, temp - mini);
            }
        }
    }

    long long maxi = LLONG_MIN;
    for (int j = 1; j <= m; ++j) {
        if (j % 2 == 0) {
            long long temp = 2 * arr[j - 1] - j;
            maxi = max(maxi, temp);
        } else {
            if (maxi != LLONG_MIN) {
                long long temp = j - 2 * arr[j - 1];
                best = max(best, maxi + temp);
            }
        }
    }

    cout << sum0 + best << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
