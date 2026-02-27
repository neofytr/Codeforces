#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)

int pw(int base, int exp) {
	base = base % MOD;
	int res = 1;
	while (exp) {
		if (exp & 1) res = res * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return res;
}

int32_t main() {
	int n, k; cin >> n >> k;
	vector<vector<pair<int, int>>> tree(n + 1);

	int u, v, x;
	for (int r = 1; r <= n; r++)
		cin >> u >> v >> x, tree[u].push_back({v, x}), tree[v].push_back({u, x});

	int res = pw(n, k);
	vector<bool> vis(n + 1, false);
	queue<int> que;
	for (int src = 1; src <= n; src++)
		if (!vis[src]) {
			int c = 0;
			que.push(src), vis[src] = true;
			while (!que.empty()) {
				int x = que.front(); que.pop();
				c++;
				for (auto [v, edge] : tree[x])
					if (!edge && !vis[v])
						vis[v] = true, que.push(v);
			}

			res = (res - pw(c, k) + MOD) % MOD;
		}

	cout << res << endl;
	return 0;
}