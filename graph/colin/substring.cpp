#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

/* int absMax = INT_MIN;

bool traverse(int node, vector<int> &letters, vector<vector<int>> &freq, vector<vector<int>> &graph, vector<bool> &done, vector<bool> &path) {
    if (done[node]) {
        return true;
    }

    path[node] = true;
    done[node] = true;
    for (int v : graph[node]) {
        if (path[v]) {
            // cycle detected in the current path
            return false;
        }

        if (!done[v]) {
            if (!traverse(v, letters, freq, graph, done, path))
                return false;
        }

        for (int letter = 0; letter < 26; letter++) {
            freq[node][letter] = max(freq[node][letter], freq[v][letter]);
        }
    }

    absMax = max(absMax, ++freq[node][letters[node]]); // since the path starts from node
    path[node] = false;
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> letters(n + 1, 0);
    char c;
    for (int node = 1; node <= n; node++) {
        cin >> c;
        letters[node] = c - 'a';
    }

    int a, b;
    vector<vector<int>> graph(n + 1, vector<int>());
    while (m--) {
        cin >> a >> b;
        graph[a].push_back(b);
    }

    vector<vector<int>> freq(n + 1, vector<int>(26, 0));
    vector<bool> done(n + 1, false);
    // freq[r][c] denotes the maximum frequency of c we can get along any path starting from
    // the node r

    for (int node = 1; node <= n; node++) {
        vector<bool> path(n + 1, false);
        if (!traverse(node, letters, freq, graph, done, path)) {
            cout << -1 << endl;
            return EXIT_SUCCESS;
        }
    }

    cout << absMax << endl;
    return EXIT_SUCCESS;
} */

// method 2

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> letters(n + 1);
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c;
        letters[i] = c - 'a';
    }

    vector<vector<int>> graph(n + 1);
    vector<vector<int>> rev(n + 1); // rev[r] tracks which nodes come into r
    vector<int> inDegree(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        rev[b].push_back(a); // a comes into b
        inDegree[b]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (!inDegree[i])
            q.push(i);

    vector<int> topo;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);
        for (int neighbor : graph[node]) {
            if (!(--inDegree[neighbor]))
                q.push(neighbor);
        }
    }

    if (topo.size() != n) {
        cout << -1 << endl; // cycle detected
        return 0;
    }

    // dp[node][letter] = max count of 'letter' on any path ending at 'node'
    vector<vector<int>> dp(n + 1, vector<int>(26, 0));
    int initNode = topo[0];
    dp[initNode][letters[initNode]]++;
    int ans = 0;
    ans = max(dp[initNode][letters[initNode]], ans);
    for (int index = 1; index < n; index++) {
        int node = topo[index];
        for (int back : rev[node]) {
            for (int c = 0; c < 26; c++) {
                dp[node][c] = max(dp[back][c], dp[node][c]);
                ans = max(ans, dp[node][c]);
            }
        };
        ans = max(ans, ++dp[node][letters[node]]);
    }

    cout << ans << endl;
    return 0;
}