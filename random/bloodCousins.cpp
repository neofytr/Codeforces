#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define LOG (18)

vector<int> tree[MAX + 1];
int depth[MAX + 1];
int tab[LOG + 1][MAX + 1];

int32_t main() {
	int n; cin >> n;
	int root;

	int v;
	for (int i = 1; i <= n; i++) {
		cin >> v;
		if (!v) {
			root = i;
			continue;
		}
		tree[v].push_back(i);
	}

	for (int i = 0; i <= LOG; i++)
		for (int j = 0; j <= n; j++) tab[i][j] = -1;
	for (int i = 0; i <= n; i++) depth[i] = -1;

	queue<int> q;

	q.push(root), depth[root] = 0, tab[0][root] = -1;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int v : tree[x])
			if (depth[v] == -1)
				depth[v] = depth[x] + 1, tab[0][v] = x, q.push(v);
	}

	for (int i = 1; i <= LOG; i++)
		for (int j = 1; j <= n; j++)
			if (tab[i - 1][j] == -1) tab[i][j] = -1;
			else tab[i][j] = tab[i - 1][tab[i - 1][j]];
	return 0;
}