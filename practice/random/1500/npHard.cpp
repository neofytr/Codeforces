#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;
	vector<vector<int>> graph(n + 1);

	int u, v;
	while (m--)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	vector<int> col(n + 1, -1); queue<int> que;
	for (int i = 1; i <= n; i++)
		if (col[i] == -1) {
			int src = i; col[src] = 1;
			que.push(src);
			while (!que.empty()) {
				int x = que.front(); que.pop();
				for (int v : graph[x])
					if (col[v] == -1)
						col[v] = !col[x], que.push(v);
					else if (col[v] == col[x]) {
						cout << -1 << endl;
						return 0;
					}
			}
		}

	vector<int> one, zero;
	for (int i = 1; i <= n; i++)
		if (!col[i]) zero.push_back(i);
		else one.push_back(i);

	cout << zero.size() << endl;
	for (int e : zero) cout << e << " ";
	cout << endl;

	cout << one.size() << endl;
	for (int e : one) cout << e << " ";
	cout << endl;
	return 0;
}