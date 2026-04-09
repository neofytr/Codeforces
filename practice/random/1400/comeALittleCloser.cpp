#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> v(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> v[r].first >> v[r].second;

	if (n == 1) {
		cout << 1 << endl;
		return;
	}

	multiset<int> x, y;
	for (int r = 1; r <= n; r++)
		x.insert(v[r].first), y.insert(v[r].second);

	int mini = LLONG_MAX;
	for (int r = 1; r <= n; r++) {
		int ex = v[r].first, ey = v[r].second;
		x.erase(x.find(ex)), y.erase(y.find(ey));

		int minx = *x.begin(), maxx = *x.rbegin();
		int miny = *y.begin(), maxy = *y.rbegin();
		int area = (maxx - minx + 1) * (maxy - miny + 1);
		if (area >= n) 
			mini = min(mini, area);
		else {
			if (minx > 1 || maxx < (int)(1e9))
				mini = min(mini, area + (maxy - miny + 1));
			if (miny > 1 || maxy < (int)(1e9))
				mini = min(mini, area + (maxx - minx + 1));
		}

		x.insert(ex), y.insert(ey);
	}

	cout << mini << endl;
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}