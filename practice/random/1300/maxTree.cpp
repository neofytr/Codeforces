#include <bits/stdc++.h>
using namespace std;

#define int long long

int dfs(int x, vector<int> &p, vector<vector<int>> &g) {
	if (g[x].empty())
		return p[x] = 1;
	if (p[x] != -1)
		return p[x];

	int m = LLONG_MIN;
	for (int v : g[x])
		m = max(m, dfs(v, p, g));

	return p[x] = m + 1;
}

void solve() {
	int n;
	cin >> n;

	int u, v, x, y;
	vector<vector<int>> g(n + 1);
	for (int r = 1; r <= n - 1; r++) {
		cin >> u >> v >> x >> y;
		if (x > y) 
			g[u].push_back(v);
		if (y >= x)
			g[v].push_back(u);
	}

	vector<int> p(n + 1, -1);
	for (int r = 1; r <= n; r++)
		if (p[r] == -1)
			dfs(r, p, g);
		
	vector<pair<int, int>> vec;
	for (int r = 1; r <= n; r++)
		vec.push_back({p[r], r});
	sort(vec.rbegin(), vec.rend());

	int i = n;
	for (auto &[val, r] : vec)
		p[r] = i--;

	for (int r = 1; r <= n; r++)
		cout << p[r] << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}