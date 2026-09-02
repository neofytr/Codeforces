#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> a[i].first, a[i].second = i;
	for (int i = 1; i <= n; i++)
		cin >> b[i].first, b[i].second = i;
	sort(a.begin() + 1, a.end()), sort(b.begin() + 1, b.end());
	for (int i = 1; i <= n; i++)
		if (a[i].second != b[i].second) {
			cout << -1 << endl;
			return;
		}
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}