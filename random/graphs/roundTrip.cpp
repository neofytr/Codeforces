#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N (int)(1e5)

int n, m; 
vector<int> graph[MAX_N + 1];
bool vis[MAX_N + 1];

void dfs(int node, int parent, vector<int> &path, set<int> &p) {
	for (int v : graph[node])
		if (!vis[v]) {
			vis[v] = true;
			path.push_back(v);
			p.insert(v);
			dfs(v, node, path, p);
			path.pop_back();
			p.erase(v);
		} else if (p.find(v) != p.end() && v != parent) {
			stack<int> st; st.push(v);
			for (int r = path.size() - 1; r >= 0; r--)
				if (path[r] != v) st.push(path[r]);
				else {
					st.push(path[r]);
					break;
				}

			cout << st.size() << endl;
			while (!st.empty())
				cout << st.top() << " ", st.pop();
			cout << endl;
			exit(0);
		}
}

int32_t main() {
	cin >> n >> m;
	int u, v;
	while (m--)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	for (int r = 1; r <= n; r++)
		if (!vis[r]) {
			vector<int> path = {r};
			set<int> p;
			vis[r] = true;
			p.insert(r);
			dfs(r, -1, path, p);
		}

	cout << "IMPOSSIBLE" << endl;
	return 0;
}