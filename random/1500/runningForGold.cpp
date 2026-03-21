#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<vector<int>> r(n + 1, vector<int>(6, 0)), v(6, vector<int>(n + 1, 0));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 5; j++)
			cin >> r[i][j], v[j][i] = r[i][j];

	for (int j = 1; j <= 5; j++) sort(v[j].begin() + 1, v[j].end());

	vector<int> c;
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		for (int j = 1; j <= 5; j++) {
			int rank = r[i][j];
			int k = lower_bound(v[j].begin() + 1, v[j].end(), rank) - v[j].begin();
			cnt += (n - k + 1);
		}

		if (cnt >= 3 * n) c.push_back(i);
	}

	for (int i : c) {
		bool ok = true;

		for (int k = 1; k <= n; k++) {
			if (i == k) continue;

			int better = 0;
			for (int j = 1; j <= 5; j++) {
				if (r[i][j] < r[k][j]) better++;
			}

			if (better < 3) {
				ok = false;
				break;
			}
		}

		if (ok) {
			cout << i << endl;
			return;
		}
	}

	cout << -1 << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}