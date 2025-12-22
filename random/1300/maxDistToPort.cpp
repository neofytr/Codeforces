#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<int> p(n + 1);
	for (int r = 1; r <= n; r++) cin >> p[r];

	int u, v;
	vector<vector<int>> graph(n + 1);
	while(m--) 
		cin >> u >> v, graph[v].push_back(u), graph[u].push_back(v);

	vector<int> dist(n + 1, LLONG_MAX);
	vector<int> c(k + 1, LLONG_MIN);
	queue<int> que;

	que.push(1);
	dist[1] = 0;
	while(!que.empty()) {
		int x = que.front();
		que.pop();

		c[p[x]] = max(c[p[x]], dist[x]);
		for (int v : graph[x])
			if (dist[v] > dist[x] + 1)
				dist[v] = dist[x] + 1, que.push(v);
	}

	for (int r = 1; r <= k; r++)
		cout << c[r] << " ";
	cout << endl;
}