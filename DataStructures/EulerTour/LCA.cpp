#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

vector<int> graph[MAX + 1];

int lin[2 * MAX + 1];
int depth[MAX + 1];
int pre[MAX + 1];
int post[MAX + 1];
int t = 0;

void dfs(int node, int parent) {
	++t;
	pre[node] = t;
	lin[t] = node;

	for (int v : graph[node])
		if (v != parent) {
			depth[v] = depth[node] + 1;
			dfs(v, node);
			++t;
			lin[t] = node;
		}

	post[node] = t;
}

int32_t main() {
	int n; cin >> n;

	int u, v;
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	depth[1] = 0;
	dfs(1, -1);
	for (int i = 1; i <= 2 * n; i++)
		cout << lin[i] << " ";
	cout << endl;
	return 0;
}