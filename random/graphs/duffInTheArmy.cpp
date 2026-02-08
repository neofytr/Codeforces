#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int n, m, q; 
vector<int> tree[MAX + 1];
int c[MAX + 1];
set<int> p[MAX + 1];

int32_t main() {
	cin >> n >> m >> q;
	int u, v;
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	for (int r = 1; r <= m; r++) 
		cin >> v, c[v]++, p[v].insert(r);

	int v, u, a;
	while(q--) {
		cin >> v >> u >> a;
	}
}