#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<vector<int>> r(n + 1, vector<int>(6, 0));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 5; j++)
			cin >> r[i][j];
	vector<bool> done(n + 1, false);

	vector<int> c;
	
	for (int i = 1; i <= n; i++)
		if (!done[i]) {
			for (int j = i + 1; (j <= n) && (!done[i]); j++) {
				int cnt = 0;
				for (int k = 1; k <= 5; k++)
					cnt += (r[i][k] < r[j][k]);
				if (cnt <= 2) done[i] = true;
				else done[j] = true;
			}

			if (!done[i]) c.push_back(i);
			done[i] = true;
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