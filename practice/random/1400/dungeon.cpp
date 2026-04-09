#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int tc) {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1), b(m + 1), c(m + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= m; r++) cin >> b[r];
	for (int r = 1; r <= m; r++) cin >> c[r];

	multiset<int> swords;
	for (int r = 1; r <= n; r++)
		swords.insert(a[r]);
	vector<pair<int, int>> d(m + 1);
	for (int r = 1; r <= m; r++) d[r] = {b[r], c[r]};

	sort(d.begin() + 1, d.end());
	int cnt = 0;
	vector<int> del;
	for (int r = 1; r <= m; r++)
		if (!d[r].second) del.push_back(d[r].first);
		else if (d[r].second < d[r].first) {
			if (swords.lower_bound(d[r].first) != swords.end()) cnt++;
		}
		else if (d[r].second >= d[r].first) {
			auto itr = swords.lower_bound(d[r].first);
			if (itr != swords.end()) {
				int v = *itr;
				cnt++;
				swords.erase(itr), swords.insert(max(v, d[r].second));
			}
		}

	sort(del.begin(), del.end());
	for (int e : del) {
		auto itr = swords.lower_bound(e);
		if (itr == swords.end()) {
			cout << cnt << endl;
			return;
		}
		cnt++, swords.erase(itr);
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		solve(tc);
	}
	return 0;
}
