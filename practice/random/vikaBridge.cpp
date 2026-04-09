#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, k;
	cin >> n >> k;

	int col;
	vector<vector<int>> colors(k + 1, vector<int>{0});
	for (int r = 1; r <= n; r++)
		cin >> col, colors[col].push_back(r);

	int mx = LLONG_MAX;
	for (int c = 1; c <= k; c++) {
		int sz = colors[c].size();

		multiset<int> s;
		for (int r = 0; r < sz - 1; r++)
			s.insert(colors[c][r + 1] - colors[c][r] - 1);
		s.insert(n + 1 - colors[c][sz - 1] - 1);

		int maxi = max(*s.rbegin() / 2, *(++s.rbegin()));
		mx = min(maxi, mx);
	}

	cout << mx << endl;
}


int32_t main() {
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}