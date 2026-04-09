#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int arr[2 + 1][MAX + 1];
bool vis[2 + 1][MAX + 1];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, -1, 0, 1};

void solve() {
    int n;
    cin >> n;

    string s1, s2;
    cin >> s1 >> s2;

    for (int r = 1; r <= n; r++)
        if (s1[r - 1] == '>')
            arr[1][r] = 0;
        else
            arr[1][r] = 1;

    for (int r = 1; r <= n; r++)
        if (s2[r - 1] == '>')
            arr[2][r] = 0;
        else
            arr[2][r] = 1;

    for (int r = 1; r <= n; r++)
        vis[1][r] = vis[2][r] = false;

    queue<pair<int, int>> que;

    vis[1][1] = true;
    que.push({1, 1});
    while (!que.empty()) {
        auto [r, c] = que.front();
        que.pop();

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 1 && nr <= 2 && nc <= n && nc >= 1) {
                if (!arr[nr][nc])
                    nc++;
                else
                    nc--;

                if (nc <= n && nc >= 1 && !vis[nr][nc])
                    que.push({nr, nc}), vis[nr][nc] = true;
            }
        }
    }

    cout << (vis[2][n] ? "YES" : "NO") << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}