#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(3 * 1e5)

int a[MAX + 1];

void solve() {
	int n; cin >> n;
	for (int r = 1; r <= n; r++) cin >> a[r];	

	vector<int> f(n + 1, -1);
	vector<vector<int>> b(n + 1);
	for (int r = 1; r <= n; r++)
		b[a[r]].push_back(r);

	for (int r = 1; r <= n; r++) {
		int s = 1;
		int m = -1;
		for (int idx : b[r])
			m = max(idx - s + 1, m), s = idx + 1;
		if (!b[r].empty())
			m = max(n - b[r].back() + 1, m);
		f[r] = m;
	}

	vector<int> k(n + 1, LLONG_MAX);
	for (int r = 1; r <= n; r++)
		if (f[r] != -1) k[f[r]] = min(k[f[r]], r);


	int mini = LLONG_MAX;
	for (int r = 1; r <= n; r++) {
		mini = min(mini, k[r]);
		cout << (mini == LLONG_MAX ? -1 : mini) << " ";
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}