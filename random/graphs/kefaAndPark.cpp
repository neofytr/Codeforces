#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

vector<int> tree[MAX + 1];
int c[MAX + 1];
int n, m;

int dfs(int node, int parent, int maxi, int curr) {
	maxi = max(maxi, curr);
	if (tree[node].size() == 1 && parent != -1) 
		return (maxi <= m ? 1 : 0);

	int cnt = 0;
	for (int v : tree[node])
		if (v != parent) 
			cnt += dfs(v, node, maxi, (c[v] ? (curr + 1) : 0));

	return cnt;
}

int32_t main() {
	cin >> n >> m;
	for (int r = 1; r <= n; r++) cin >> c[r];

	int u, v;
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	cout << dfs(1, -1, LLONG_MIN, c[1]) << endl;
	return 0;
}