#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	int p, root = 1;
	vector<vector<int>> tree(n + 1);
	vector<int> a(n + 1);

	for (int i = 2; i <= n; i++)
		cin >> p, tree[p].push_back(i);
	for (int i = 1; i <= n; i++) cin >> a[i];

}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}