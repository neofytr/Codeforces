#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

vector<int> tree[MAX + 1];
int d[MAX + 1];
int peven[MAX + 1];
int podd[MAX + 1];

void dfs(int node, int parent, int depth) {
	d[depth]++;
	for (int v : tree[node])
		if (v != parent) 
			dfs(v, node, depth + 1);
}

int32_t main() {
	int n; cin >> n;

	int u, v;
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	dfs(1, -1, 1);
	
	peven[0] = 0;
	for (int r = 2; r <= MAX; r += 2)
		peven[r] += peven[r - 2] + d[r];

	podd[1] = d[1];
	for (int r = 3; r <= MAX; r += 2)
		podd[r] += podd[r - 2] + d[r];

	int cnt = 0;
	for (int r = 1; r <= MAX - 1; r++)
		if (!d[r]) break;
		else {
			if (r & 1) 
				cnt += (peven[MAX] - peven[r - 1]) * d[r] - d[r + 1];
			else 
				cnt += (podd[MAX - 1] - podd[r - 1]) * d[r] - d[r + 1];
		}

	cout << cnt << endl;
}