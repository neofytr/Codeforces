#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define LOG (18)

vector<int> tree[MAX + 1];
int depth[MAX + 1];
int lin[MAX + 1], start[MAX + 1], finish[MAX + 1];
int tab[LOG + 1][MAX + 1];

int walk(int u, int k) {
	int curr = u;
	for (int bit = 0; bit <= LOG; bit++)
		if (k & (1ll << bit)) {
			curr = tab[bit][curr];
			if (curr == -1) return curr;
		}
	return curr;
}

int t = 0;
void dfs(int node) {
	++t;
	start[node] = t;
	lin[t] = depth[node];

	for (int v : tree[node])
		dfs(v);

	finish[node] = t;
}

int32_t main() {
	int n; 
	cin >> n;

	vector<int> roots;

	for (int i = 1; i <= n; i++) {
		int v; 
		cin >> v;

		if (!v) roots.push_back(i);
		else tree[v].push_back(i);
	}

	// connect super-root 0 to all roots
	for (int r : roots)
		tree[0].push_back(r);

	for (int i = 0; i <= LOG; i++)
		for (int j = 0; j <= n; j++)
			tab[i][j] = -1;

	for (int i = 0; i <= n; i++)
		depth[i] = -1;

	queue<int> q;
	q.push(0);
	depth[0] = -1;
	tab[0][0] = -1;

	while (!q.empty()) {
		int x = q.front(); 
		q.pop();

		for (int v : tree[x]) {
			depth[v] = depth[x] + 1;
			tab[0][v] = x;
			q.push(v);
		}
	}

	for (int i = 1; i <= LOG; i++)
		for (int j = 0; j <= n; j++)
			if (tab[i - 1][j] == -1)
				tab[i][j] = -1;
			else
				tab[i][j] = tab[i - 1][tab[i - 1][j]];

	dfs(0);

	vector<vector<int>> f(n + 2);

	for (int i = 1; i <= t; i++)
		if (lin[i] >= 0)
			f[lin[i]].push_back(i);

	int m; 
	cin >> m;

	while (m--) {
		int v, p; 
		cin >> v >> p;

		v = walk(v, p);

		if (v == 0 || v == -1) {
			cout << 0 << " ";
			continue;
		}

		int l = start[v], r = finish[v];

		int target = depth[v] + p;

		if (target >= f.size()) {
			cout << 0 << " ";
			continue;
		}

		cout << upper_bound(f[target].begin(), f[target].end(), r)
		       - lower_bound(f[target].begin(), f[target].end(), l) - 1
		     << " ";
	}

	cout << endl;

	return 0;
}