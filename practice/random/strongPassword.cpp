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

	vector<int> first(9, -1);
	for (int i = 1; i <= n; i++)
		if (first[str[i]] == -1)
			first[str[i]] = i;

	cin >> m;
	string l, r; cin >> l >> r;
	vector<int> low(m + 1), up(m + 1);
	for (int i = 1; i <= m; i++) 
		low[i] = l[i - 1] - '0', up[i] = r[i - 1] - '0';

	if (m == 1) {
		for (int i = low[1]; i <= up[1]; i++)
			if (first[i] == -1) {
				cout << "YES" << endl;
				return;
			}

		cout << "NO" << endl;
		return;
	}

	for (int i = low[1]; i <= up[1]; i++) {
		if (first[i] == -1) {
			cout << "YES" << endl;
			return;
		}

		set<int> s;
		for (int j = first[i] + 1; j <= n; j++)
			s.insert(str[j]);

		for (int j = low[2]; j <= up[2]; j++)
			if (s.find(j) == s.end()) {
				cout << "YES" << endl;
				return;
			}
	}

	cout << "NO" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}