#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <queue>
#include <unistd.h>
#include <vector>
using namespace std;

int traverse(int x, int m, vector<int> &dist) {
    dist[x] = 0;
    queue<int> que;
    que.push(x);

    while (!que.empty()) {
        int size = (int)que.size();
        // process the current depth
        while (size--) {
            int node = que.front();
            que.pop();

            if (node - 1 >= 0 && dist[node - 1] == -1) {
                dist[node - 1] = dist[node] + 1;
                que.push(node - 1);
            }
            if (2 * node < (int)dist.size() && dist[2 * node] == -1) {
                dist[2 * node] = dist[node] + 1;
                que.push(2 * node);
            }
        }
    }

    return dist[m];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> dist(2 * (max(n, m) + 1), -1);
    cout << traverse(n, m, dist) << endl;
    return EXIT_SUCCESS;
}