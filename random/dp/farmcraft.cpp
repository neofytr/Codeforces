#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(5 * 1e5)

int n;
int c[MAX + 1];
vector<int> tree[MAX + 1];
int dp[MAX + 1];
int sz[MAX + 1];

auto cmp = [](int a, int b) -> bool {
	int m1 = max(1 + dp[a], 1 + 2 * sz[a] + 2 + dp[b]);
	int m2 = max(1 + dp[b], 1 + 2 * sz[b] + 2 + dp[a]);
	if (m1 <= m2) return true;
	return false;
};

int s(int node, int p) {
	sz[node] = 1;
	for (int x : tree[node])
		if (x != p)
			sz[node] += s(x);
	return sz[node];
}

int cnt(int node, int p) {
	if (node == 1) dp[node] = max(dp[node], 2 * (n - 1) + c[1]);
	else dp[node] = max(dp[node], c[node]);

	if (tree[node].size() == 1) return dp[node];

	for (int x : tree[node])
		if (x != p)
			cnt(x, node);
	sort(tree[node].begin(), tree[node].end(), cmp);

	int t = 0;
	for (int x : tree[node]) {
		if (x == p) continue;
		t++;
		dp[node] = max(dp[node], t + dp[x]);
		t += 2 * sz[x] + 1;
	}

	return dp[node];
}

int32_t main() {
	cin >> n;
	

	int a, b;
	for (int r = 1; r <= n - 1; r++)
		cin >> a >> b, tree[a].push_back(b), tree[b].push_back(a);

	for (int r = 1; r <= n; r++)
		cin >> c[r];

	s(1);
	cout << cnt(1) << endl;
	return 0;
}