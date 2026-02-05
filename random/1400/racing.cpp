#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> d(n + 1);
	for (int r = 1; r <= n; r++) cin >> d[r];

	vector<pair<int, int>> p(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> p[i].first >> p[i].second;

	int maxones = 0, minones = 0;
	for (int i = 1; i <= n; i++) {
		auto [l, r] = p[i];
		if (!d[i]) {
			if (maxones < l) {
				cout << -1 << endl;
				return;
			}
			if (minones > r) {
				cout << -1 << endl;
				return;
			}

			maxones = min(r, maxones);
			minones = max(l, minones);
			continue;
		}

		if (d[i] == 1) {
			maxones++, minones++;
			if (maxones < l) {
				cout << -1 << endl;
				return;
			}
			if (minones > r) {
				cout << -1 << endl;
				return;
			}

			maxones = min(r, maxones);
			minones = max(l, minones);
			continue;
		}

		if (d[i] == -1) {
			maxones++;
			if (maxones < l) {
				cout << -1 << endl;
				return;
			}
			if (minones > r) {
				cout << -1 << endl;
				return;
			}

			if (minones < l)
				d[i] = 1;
			else 
				d[i] = 0;
			maxones = min(r, maxones);
			minones = max(l, minones);
		}
	}
	for (int r = 1; r <= n; r++)
		cout << d[r] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}