#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: moocast
// URL: https://usaco.org/index.php?page=viewproblem2
// Difficulty: hard
// Tags: 
// Strategy: 

#define MAX_N (1000)
pair<int, int> coords[MAX_N + 1];
bool vis[MAX_N + 1];
int cnt = 0;
int nodesN = 0;

void dfs(int maxi, int node) {
    vis[node] = true;
    cnt++;
    int X = coords[node].first;
    int Y = coords[node].second;
    for (int r = 1; r <= nodesN; r++) {

        int x = coords[r].first;
        int y = coords[r].second;

        if ((X - x) * (X - x) + (Y - y) * (Y - y) <= maxi && !vis[r])
            dfs(maxi, r);
    }
}

bool can(int x) {
    cnt = 0;
    memset(vis, 0, sizeof(vis)); 
    dfs(x, 1);
    return cnt == nodesN;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    cin >> nodesN;
    for (int r = 1; r <= nodesN; r++) 
        cin >> coords[r].first >> coords[r].second;

    int left = -1;
    int right = 25000LL * 25000LL * 2 + 1; 

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (can(mid))
            right = mid;
        else 
            left = mid;
    }
    cout << right << endl;
    return 0;
}
