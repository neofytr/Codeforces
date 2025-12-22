#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<int> teachers(m + 1);
	for (int r = 1; r <= m; r++) cin >> teachers[r];

	sort(teachers.begin() + 1, teachers.end());
	int a;
	while (q--) {
		cin >> a;

		// teacher nearest to david from the right
		auto rightitr = lower_bound(teachers.begin() + 1, teachers.end(), a);
		if (rightitr != teachers.begin() + 1 && rightitr != teachers.end()) {
			auto leftitr = rightitr - 1;
			int right = *rightitr, left = *leftitr;
		}
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}