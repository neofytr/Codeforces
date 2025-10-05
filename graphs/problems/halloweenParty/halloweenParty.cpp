#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: halloweenParty
// URL: https://web.archive.org/web/20200930162803/http://www.devskill.com/CodingProblems/ViewProblem/60
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    for (int r = 1; r <= t; r++) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> city(n, vector<int>(m));
        for (int row = 0; row < n; row++) {
            string str;
            cin >> str;
            for (int col = 0; col < m; col++)
                city[row][col] = str[col] - '0';
        }

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, -1, 0, 1};

        deque<pair<int, int>> que;
        vector<vector<int>> dist(n, vector<int>(m, LLONG_MAX));

        que.push_front({0, 0});
        dist[0][0] = 0;
        while(!que.empty()) {
            auto [r, c] = que.front();
            que.pop_front();
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nc >= 0 && nr < n && nc < m) {
                    int w = (city[nr][nc] == city[r][c] ? 0 : 1);
                    if (dist[nr][nc] > dist[r][c] + w) {
                        dist[nr][nc] = dist[r][c] + w;
                        if (!w) que.push_front({nr, nc});
                        else que.push_back({nr, nc});
                    }
                }
                    
            }
        }

        cout << "Case " << r << ": " << dist[n - 1][m - 1] << endl;
    }    
    return 0;
}