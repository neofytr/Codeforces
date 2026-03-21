#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<vector<int>> r(n + 1, vector<int>(5, 0));
	vector<int> one, two;
	bool found = false, ans = -1;
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		for (int j = 1; j <= 5; j++) {
			cin >> r[i][j];
			if (r[i][j] == 1) cnt++;
		}

		if (cnt >= 3) {
			found = true;
			ans = i;
		}
		if (cnt == 2) two.push_back(i);
		if (cnt == 1) one.push_back(i);
	}

	if (found) {
		cout << ans << endl;
		return;
	}

	for (int i : two) {
		vector<int> b(n + 1, 2);
		b[i]++;

		for (int j = 1; j <= 5; j++)
			if (r[i][j] != 1)
				for (int k = 1; k <= n; k++)
					if (r[i][j] < r[k][j]) b[k]++;

		bool done = true;
		for (int j = 1; j <= n; j++)
			if (b[j] < 3) {
				done = false;
				break;
			}

		if (done) {
			cout << i << endl;
			return;
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}