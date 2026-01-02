#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int str[MAX + 1];
int nxt[MAX + 1][26];

void solve() {
    string s;
    cin >> s;

    int n = (int)s.length();
    for (int r = 1; r <= n; r++)
        str[r] = s[r - 1] - 'a';
    for (int c = 0; c < 26; c++)
        nxt[n][c] = LLONG_MAX;

    for (int r = n - 1; r >= 1; r--)
        for (int c = 0; c < 26; c++)
            if (str[r + 1] == c)
                nxt[r][c] = r + 1;
            else
                nxt[r][c] = nxt[r + 1][c];

    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({0, {1, 2}});

    while (!pq.empty()) {
        auto [c, p] = pq.top();
        pq.pop();

        int i = p.first, j = p.second;
        cout << c << " " << i << " " << j << endl;
        if (i >= n) {
            cout << c << endl;
            return;
        }

        int nxti = nxt[i][str[i]], nxtj = nxt[j][str[j]];
        if (nxti != LLONG_MAX) {
            pq.push({c + (nxti - 1) - (i + 1) + 1, {nxti + 1, nxti + 2}});
        }
        if (nxtj != LLONG_MAX) {
            pq.push({c + (nxtj - 1) - (j + 1) + 2, {nxtj + 1, nxtj + 2}});
        }
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