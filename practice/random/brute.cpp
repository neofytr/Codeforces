#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> bad(n + 1);
        set<pair<int, int>> seen;
        while (m--) {
            int x, y;
            cin >> x >> y;
            if (!seen.count({x, y}) && !seen.count({y, x})) {
                bad[x].push_back(y);
                bad[y].push_back(x);
                seen.insert({x, y});
                seen.insert({y, x});
            }
        }

        long long brute_ans = 0;
        for (int l = 1; l <= n; ++l) {
            for (int r = l; r <= n; ++r) {
                bool ok = true;
                // Check every bad pair (x,y)
                for (int i = l; i <= r && ok; ++i) {
                    for (int e : bad[i]) {
                        if (e >= l && e <= r) {
                            ok = false;
                            break;
                        }
                    }
                }
                if (ok) brute_ans++;
            }
        }

        cout << "Brute-force correct answer: " << brute_ans << "\n";
    }
}
