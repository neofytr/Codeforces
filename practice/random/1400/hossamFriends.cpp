#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m;
	cin >> n >> m;

	// the property good is subsegment monotonic
	int a, b;
	vector<set<int>> vec(n + 1);
	for (int r = 1; r <= m; r++)
		cin >> a >> b, vec[a].insert(b), vec[b].insert(a);

	int cnt = 0;
	int l = 1;
	for (int r = 1; r <= n; r++) {
		int k = -1;
		if (!vec[r].empty()) {
			auto itr = vec[r].lower_bound(r);
			if (itr != vec[r].begin()) k = *(--itr);
		}

		while (l <= r && l <= k)
			l++;

		if (l <= r) 
			cnt += (r - l + 1);
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}