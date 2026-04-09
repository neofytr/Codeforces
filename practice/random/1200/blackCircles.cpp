#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<pair<int, int>> v(n + 1);
	for (int r = 1; r <= n; r++) cin >> v[r].first >> v[r].second;

	pair<int, int> start, finish;
	cin >> start.first >> start.second >> finish.first >> finish.second;
	set<int> d;	

	for (int r = 1; r <= n; r++) {
		int x = v[r].first - finish.first;
		int y = v[r].second - finish.second;
		d.insert(x * x + y * y);
	}

	int x = start.first - finish.first, y = start.second - finish.second;
	int res = x * x + y * y;

	if (*d.begin() <= res)
		cout << "NO\n";
	else
		cout << "YES\n";
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}