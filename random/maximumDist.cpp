#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m, k;
	cin >> n >> m >> k;

	int tmp;
	vector<vector<int>> type(k + 1);
	for (int r = 1; r <= n; r++)
		cin >> tmp, type[tmp].push_back(r);

	int u, v;
	vector<vector<int>> graph(n + 1);
	for (int r = 1; r <= m; r++)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	int src = 1;
	vector<int> dist(n + 1, LLONG_MAX);
	queue<int> que;

	que.push(src);
	dist[src] = 0;
	while(!que.empty()) {
		int x = que.front();
		que.pop();

		for (int v : graph[x])
			if (dist[x] + 1 < dist[v])
				dist[v] = dist[x] + 1, que.push(v);
	}

	for (int t = 1; t <= k; t++) {
		int maxi = -1;
		for (int city : type[t])
			maxi = max(maxi, dist[city]);
		cout << maxi << " ";
	}
	cout << endl;
	return 0;
}