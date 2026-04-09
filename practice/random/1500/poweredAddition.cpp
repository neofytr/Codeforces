#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];

	priority_queue<pair<int, int>> pq;
	for (int r = 1; r <= n; r++) pq.push({a[r], r});

	int last = n;
	int maxi = 0;
	while (!pq.empty()) {
		auto [elt, idx] = pq.top(); pq.pop();
		if (idx > last) continue;

		int mini = LLONG_MAX;
		for (int r = idx; r <= last; r++) mini = min(mini, a[r]);

		int d = elt - mini;
		last = idx;

		if (!d) continue;
		maxi = max(maxi, 64ll - __builtin_clzll(d));
	}

	cout << maxi << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}