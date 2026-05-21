#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m;
	string s; cin >> s;
	n = s.length();
	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++) 
		str[i] = s[i - 1] - '0';

	cin >> m;
	string l, r; cin >> l >> r;
	vector<int> low(m + 1), up(m + 1);
	for (int i = 1; i <= m; i++) 
		low[i] = l[i - 1] - '0', up[i] = r[i - 1] - '0';

	vector<set<int>> f(10);
	for (int i = 1; i <= n; i++)
		f[str[i]].insert(i);

	vector<int> ear(10, -1), tmp(10, -1);
	for (int i = low[1]; i <= up[1]; i++)
		if (!f[i].empty()) ear[i] = *f[i].begin();
		else {
			cout << "YES" << endl;
			return;
		}

	for (int i = 2; i <= m; i++) {
		for (int j = low[i]; j <= up[i]; j++) {
			tmp[j] = -1;
			for (int k = low[i - 1]; k <= up[i - 1]; k++)
				if (f[j].lower_bound(ear[k] + 1) == f[j].end()) {
					cout << "YES" << endl;
					return;
				} else 
					tmp[j] = max(tmp[j], *f[j].lower_bound(ear[k] + 1));
		}
		swap(tmp, ear);
	}

	cout << "NO" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}