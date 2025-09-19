#include <bits/stdc++.h>
using namespace std;

#define int long long

// problem: divisiblepairs
// url: https://codeforces.com/problemset/problem/1931/d
// difficulty: medium
// tags:
// strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

// problem: divisiblepairs
// url: https://codeforces.com/problemset/problem/1931/d
// difficulty: medium
// tags:
// strategy:

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;

        map<pair<int, int>, int> mp;
        int val;
        int cnt = 0;
        for (int r = 1; r <= n; r++) {
            cin >> val;
            const int r1 = val % x;
            const int r2 = val % y;

            int need = (x - r1) % x;
            cnt += mp[{need, r2}];
            mp[{r1, r2}]++;
        }
        cout << cnt << endl;
    }
    return 0;
}