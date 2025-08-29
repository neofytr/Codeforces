#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int64> a(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        int64 ops = 0;
        for (int i = 1; i <= n; i += 2) { // only odd indices
            int64 limit;
            if (i == 1)
                limit = a[2];
            else if (i == n)
                limit = a[n - 1];
            else
                limit = min(a[i - 1], a[i + 1]);
            if (a[i] > limit)
                ops += (a[i] - limit);
        }
        cout << ops << "\n";
    }
    return 0;
}
