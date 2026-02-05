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
	vector<int> mini(n + 1), maxi(n + 1);
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
			maxones = min(r, maxones);
			minones = max(l, minones);
		}

		mini[i] = minones, maxi[i] = maxones;
	}

	int cnt = 0;
	vector<int> idx;
	for (int r = 1; r <= n; r++) {
		if (d[r] == -1) idx.push_back(r);
		if (d[r] == 1) cnt++;
		while (cnt < mini[r])
			d[*idx.rbegin()] = 1, cnt++, idx.pop_back();
	}

	for (int r = 1; r <= n; r++)
		cout << (d[r] == -1 ? 0 : d[r]) << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}