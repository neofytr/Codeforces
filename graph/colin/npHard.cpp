// https://codeforces.com/gym/317667/problem/D

#include <bits/stdc++.h>
#include <cstdlib>
#include <ostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>());
    int a, b;
    while (m--) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> cover(n + 1, -1);
    for (int node = 1; node <= n; node++) {
        if (cover[node] == -1) {
            cover[node] = 0;
            queue<int> que;
            que.push(node);

            while (!que.empty()) {
                int x = que.front();
                que.pop();

                for (int v : graph[x]) {
                    if (cover[v] == -1) {
                        cover[v] = !cover[x] ? 1 : 0;
                        que.push(v);
                    } else if (cover[v] == cover[x]) {
                        cout << -1 << "\n";
                        return EXIT_SUCCESS;
                    }
                }
            }
        }
    }

    int k = 0;
    for (int node = 1; node <= n; node++) {
        if (!cover[node]) {
            k++;
        }
    }

    cout << k << endl;
    for (int node = 1; node <= n; node++) {
        if (!cover[node])
            cout << node << " ";
    }
    cout << endl;
    cout << n - k << endl;

    for (int node = 1; node <= n; node++) {
        if (cover[node]) {
            cout << node << " ";
        }
    }
    cout << endl;
    return EXIT_SUCCESS;
}