#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (998244353)

void solve() {
	int n, m; cin >> n >> m;
	int u, v;
	vector<vector<int>> graph(n + 1);
	while (m--)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	queue<int> que;
	vector<int> color(n + 1, -1);
	int res = 1;
	for (int node = 1; node <= n; node++)
		if (color[node] == -1) {
			vector<int> elts;
			que.push(node), color[node] = 0;
			while (!que.empty()) {
				int x = que.front(); que.pop();
				elts.push_back(x);
				for (int v : graph[x])
					if (color[v] == -1)
						color[v] = !color[x], que.push(v);
					else if (color[v] == color[x]) {
						cout << 0 << endl;
						return;
					}
			}
			int cnt1 = 1;
			for (int e : elts)
				if (color[e]) cnt1 = (cnt1 * 2) % MOD;
			int cnt2 = 1;
			for (int e : elts)
				if (!color[e]) cnt2 = (cnt2 * 2) % MOD;
			res = res * ((cnt1 + cnt2) % MOD) % MOD;
		}

	cout << res << endl;
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}