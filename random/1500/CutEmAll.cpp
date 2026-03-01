#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int n, u, v;
int cnt = 0;

vector<int> tree[MAX + 1];
int dfs(int node, int parent) {
	if (tree[node].size() == 1 && parent != -1)
		return 1;

	int res = 1;
	for (int x : tree[node])
		if (x != parent) {
			int v = dfs(v, node);
			if (!(v % 2) && (!(n - v) % 2)) cnt++;
			res += v;
		}

	return res;
}

int32_t main() {
	cin >> n;
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	dfs(1, -1);
	cout << cnt << endl;
	return 0;
}