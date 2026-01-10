#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    string col;
    vector adj(n + 1, vector<int>(n + 1, 0));
    for (int r = 1; r <= n; r++) {
        cin >> col;
        for (int c = 1; c <= n; c++)
            adj[r][c] = col[c - 1] - '0';
    }

    vector<int> indegree(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (adj[i][j])
                indegree[j]++;

    priority_queue<int> pq;
    for (int r = 1; r <= n; r++)
        if (!indegree[r])
            pq.push(r);

    vector<int> p;
    while (!pq.empty()) {
        const int x = pq.top();
        pq.pop();

        p.push_back(x);
        for (int i = x + 1; i <= n; i++)
            if (adj[x][i] && !(--indegree[i]))
                pq.push(i);
    }

    for (const int e : p)
        cout << e << " ";
    cout << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}