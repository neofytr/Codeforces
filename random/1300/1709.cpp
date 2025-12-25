#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> a(n + 1), b(n + 1);
	vector<pair<int, int>> f(2 * n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r], f[a[r]] = {0, r};
	for (int r = 1; r <= n; r++) cin >> b[r], f[b[r]] = {1, r};

	int alast = n, blast = n;
	vector<pair<int, int>> ops;
	
	int alast = n, blast = n;
	for (int r = 2 * n; r--; r >= 1) {
		auto [arrnum, idx] = f[r];
		if (r == 2 * n) {
			if (!arrnum) {
				for (int r = idx; r <= n - 1; r++)
					ops.push_back({1, r}), f[a[r + 1]] = {0, r}, swap(a[r], a[r + 1]);
			}
		}
	}

	
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
}