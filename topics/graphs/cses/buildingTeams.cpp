#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

#define TEAMA 0
#define TEAMB 1

int main() {
    int n, m;
    cin >> n >> m;

    int a, b;
    vector<vector<int>> graph(n + 1);
    while (m--) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> team(n + 1, -1);
    queue<int> que;

    for (int node = 1; node <= n; node++) {
        if (team[node] == -1) {
            // not been visited till now
            int src = node;    // arbitrary
            team[src] = TEAMA; // arbitrary
            que.push(src);
            while (!que.empty()) {
                int x = que.front();
                que.pop();

                for (int v : graph[x]) {
                    if (team[v] == -1) {
                        // node has not been visited till now
                        team[v] = !team[x];
                        que.push(v);
                    } else if (team[v] == team[x]) {
                        // v has been assigned a color before and it's same as the color of it's parent
                        cout << "IMPOSSIBLE\n";
                        return EXIT_SUCCESS;
                    }
                }
            }
        }
    }

    for (int node = 1; node <= n; node++)
        cout << team[node] + 1 << " ";
    cout << endl;
    return EXIT_SUCCESS;
}