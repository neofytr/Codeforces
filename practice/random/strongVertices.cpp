#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];

	vector<pair<int, int>> t(n);
	for (int i = 0; i < n; i++) t[i] = {a[i + 1] - b[i + 1], i};

	sort(t.begin(), t.end()); reverse(t.begin(), t.end());
	int m = t[0].first;

	int i = 0;
	while (i < n && t[i].first == m) i++;

	set<int> res;
	for (int j = 0; j < i; j++) res.insert(t[j].second);
	cout << res.size() << endl;
	for (int e : res)
		cout << e + 1 << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}