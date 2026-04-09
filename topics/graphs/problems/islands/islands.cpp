#include <bits/stdc++.h>
using namespace std;

void traverse(int row, int col, vector<vector<int>> &visited, const vector<vector<int>> &graph) {
    int n = visited.size();
    int m = visited[0].size();

    if (row < 0 || col < 0 || row >= n || col >= m)
        return;
    if (visited[row][col] || !graph[row][col])
        return;

    visited[row][col] = 1;

    traverse(row + 1, col, visited, graph);
    traverse(row - 1, col, visited, graph);
    traverse(row, col + 1, visited, graph);
    traverse(row, col - 1, visited, graph);
    traverse(row + 1, col + 1, visited, graph);
    traverse(row - 1, col - 1, visited, graph);
    traverse(row - 1, col + 1, visited, graph);
    traverse(row + 1, col - 1, visited, graph);
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n, vector<int>(m));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            cin >> graph[row][col];
        }
    }

    vector<vector<int>> visited(n, vector<int>(m, 0));
    int count = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (graph[row][col] == 1 && !visited[row][col]) {
                count++;
                traverse(row, col, visited, graph);
            }
        }
    }

    cout << count << endl;
    return 0;
}
