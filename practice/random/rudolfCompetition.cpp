#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m, h; cin >> n >> m >> h;
	vector<vector<int>> t(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			cin >> t[r][c];

	vector<tuple<int, int, int>> f;
	for (int i = 1; i <= n; i++) {
		int pen = 0, p = 0;
		int sum = 0;
		sort(t[i].begin() + 1, t[i].end());
		for (int j = 1; j <= m; j++)
			if (sum + t[i][j] <= h)
				p++, sum += t[i][j], pen += sum;
			else 
				break;
		f.push_back({p, pen, i});
	}

	sort(f.begin(), f.end(), [](auto &one, auto &two){
		auto [onep, onepen, onei] = one;
		auto [twop, twopen, twoi] = two;
		if (onep > twop) return true;
		if (onep == twop && onepen < twopen) return true;
		if (onep == twop && onepen == twopen && onei < twoi) return true;
		return false;
	});

	for (int i = 0; i < n; i++) {
		auto [p, pen, j] = f[i];
		if (j == 1) {
			cout << i + 1 << endl;
			return;
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}