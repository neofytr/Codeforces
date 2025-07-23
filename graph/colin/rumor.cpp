// https://codeforces.com/gym/317667/problem/B

#include <bits/stdc++.h>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

void findMin(int node, vector<bool> &visited, vector<vector<int>> &graph, vector<long long> &gold, long long *minimum) {
    visited[node] = true;
    *minimum = min(*minimum, gold[node]);
    for (int v : graph[node]) {
        if (!visited[v]) {
            findMin(v, visited, graph, gold, minimum);
        }
    }
    return;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>());
    vector<long long> gold(n + 1, 0);
    for (int index = 1; index <= n; index++)
        cin >> gold[index];

    int a, b;
    while (m--) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // to finish the quest by using the minimum amount of gold
    // , we pass the rumor onto the cheapest friend in a group of friends (connected-component)

    long long total = 0;
    vector<bool> visited(n + 1, false);
    for (int node = 1; node <= n; node++) {
        if (!visited[node]) {
            long long minimum = LLONG_MAX;
            findMin(node, visited, graph, gold, &minimum);
            total += minimum;
        }
    }

    cout << total << endl;
    return EXIT_SUCCESS;
}