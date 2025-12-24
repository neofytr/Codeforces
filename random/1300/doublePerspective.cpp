#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<pair<int, pair<int, int>>> p(n + 1);
	for (int i = 1; i <= n; i++) 
		cin >> p[i].first >> p[i].second.first, p[i].second.second = i;
	
	sort(p.begin() + 1, p.end());
	int left = LLONG_MAX, right = LLONG_MIN;
	vector<int> res;
	for (int r = 1; r <= n; r++) {
		auto [lft, v] = p[r];
		int rght = v.first, idx = v.second;
		if (lft == left && right == rght)
			continue;

		if (rght <= right)
			continue;

		res.push_back(idx);
		if (lft < right || lft > right) {
			left = lft, right = rght;
			continue;
		}

		if (lft == right)
			right = rght;
	}

	cout << res.size() << endl;
	for (int r : res)
		cout << r << " " ;
	cout << endl;
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
