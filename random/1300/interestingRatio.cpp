#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e7)

vector<int> spf(MAX + 1, -1);

void solve() {
    int n;
    cin >> n;

    int cnt = 0;
    for (int b = 2; b <= n; b++) {
        int x = b;
        int num = 0;
        while (x != 1) {
            const int p = spf[x];
            while (!(x % p))
                x /= p;
            num++;
        }
        cnt += num;
    }

    cout << cnt << endl;
}

int32_t main() {
    int t;
    cin >> t;

    for (int r = 2; r <= MAX; r++)
        if (spf[r] == -1)
            for (int j = r; j <= MAX; j += r)
                if (spf[j] == -1)
                    spf[j] = r;

    while (t--) {
        solve();
    }
    return 0;
}