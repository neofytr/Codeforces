// https://codeforces.com/problemset/problem/977/E

#include <bits/stdc++.h>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

bool traverse(int node, vector<bool> &visited, vector<vector<int>> &graph) {
    visited[node] = true;
    queue<pair<int, int>> que;
    que.push({node, -1});
    int result = -1;
    int tempNode = -1;

    while (!que.empty()) {
        auto elt = que.front();
        int vert = elt.first;
        int parent = elt.second;
        que.pop();

        if (parent == -1) {
            int count = 0;
            for (int v : graph[vert]) {
                if (!visited[v]) {
                    visited[v] = true;
                    que.push({v, vert});
                    count++;
                }

                if (count >= 3)
                    result = 0;
            }

            if (count == 2) {
                auto temp = que.front();
                que.pop();
                tempNode = temp.first;
                visited[temp.first] = false;
            }
        } else {
            int count = 0;
            bool seenFinal = false;
            for (int v : graph[vert]) {
                if (!visited[v]) {
                    visited[v] = true;
                    que.push({v, vert});
                    count++;
                }

                if (count >= 2)
                    result = 0;

                if (v == node && parent != node) {
                    seenFinal = true;
                }
            }

            if (seenFinal && result == -1) {
                result = 1;
            }
        }
    }

    if (tempNode != -1) {
        visited[tempNode] = true;
    }
    if (result == 1)
        return true;
    else
        return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    int a, b;
    while (m--) {
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<bool> visited(n, false);
    int count = 0;
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            count += traverse(node, visited, graph) ? 1 : 0;
        }
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}