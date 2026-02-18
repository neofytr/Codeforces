#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;

	vector<vector<bool>> exist(n + 2, vector<bool>(2, false));
	int zero = 0, one = 0;

	vector<pair<int, int>> pts;
	for (int r = 1; r <= n; r++) {
		int x, y; cin >> x >> y;
		pts.push_back({x, y});
		exist[x][y] = true;
		if (!y) zero++;
		else one++;
	}

	int cnt = 0;
	for (auto &[x, y] : pts) {
		if (y) {
			if (exist[x][0]) cnt += (one - 1);
			if (x >= 1 && exist[x - 1][0] && exist[x + 1][0]) cnt++;
		} else {
			if (exist[x][1]) cnt += (zero - 1);
			if (x >= 1 && exist[x - 1][1] && exist[x + 1][1]) cnt++;
		}
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}