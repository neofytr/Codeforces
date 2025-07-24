#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

int absMax = INT_MIN;

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
}