#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m;
	string s; cin >> s;
	n = s.length();
	vector<int> pass(n + 1);
	for (int i = 1; i <= n; i++) 
		pass[i] = s[i - 1] - '0';

	cin >> m;
	string l, r; cin >> l >> r;
	vector<int> low(m + 1), up(m + 1);
	for (int i = 1; i <= m; i++) 
		low[i] = l[i - 1] - '0', up[i] = r[i - 1] - '0';
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}