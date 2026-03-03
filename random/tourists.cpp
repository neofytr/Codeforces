#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)
#define LOG (18)

int n;
int tab[LOG][MAX + 1];
int depth[MAX + 1];
vector<int> tree[MAX + 1];

int walk(int u, int k) {
	int curr = u;
	for (int bit = 0; bit <= LOG; bit++)
		if (k & (1ll << bit)) {
			curr = tab[bit][curr];
			if (curr == -1) return curr;
		}

	return curr;
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) swap(v, u);
	u = walk(u, depth[u] - depth[v]);

	if (u == v) return v;
}

int32_t main() {
	cin >> n;
	int u, v;
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	for (int i = 0; i <= n; i++) depth[i] = -1;
	for (int i = 0; i <= LOG; i++)
		for (int j = 0; j <= n; j++)
			tab[i][j] = -1;

	int root = 1;
	queue<int> q;

	q.push(root);
	depth[root] = 0;
	tab[0][root] = -1;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		int d = depth[x];

		for (int v : tree[x])
			if (depth[v] == -1)
				depth[v] = d + 1, tab[0][v] = x, q.push(v); 
	}

	for (int i = 1; i <= LOG; i++)
		for (int j = 1; j <= n; j++) {
			if (tab[i - 1][j] == -1) tab[i][j] = -1;
			else tab[i][j] = tab[i - 1][tab[i - 1][j]];
		}

	return 0;
}