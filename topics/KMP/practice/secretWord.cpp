#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	string s; cin >> s;
	string t = s;
	reverse(t.begin(), t.end());

	int n = t.length();
	vector<int> p(n + 1, 0);

	int j = 0;
	for (int i = 2; i <= n; i++) {
		while (j > 0 && s[j + 1 - 1] != s[i - 1])
			j = p[j];
		if (s[j + 1 - 1] == s[i - 1])
			++j;
		p[i] = j;
	}

	j = 0;
	int m = 0;
	for (int i = 1; i <= n; i++) {
		while (j > 0 && s[j + 1 - 1] != t[i - 1])
			j = p[j];
		if (s[j + 1 - 1] == t[i - 1])
			++j;
		m = max(m, j);
		if (j == n)
			j = p[j];
	}

	j = 0;
	for (int i = 1; i <= n; i++) {
		while (j > 0 && s[j + 1 - 1] != t[i - 1])
			j = p[j];
		if (s[j + 1 - 1] == t[i - 1])
			++j;
		if (m == j) {
			string c = s.substr(0, m);
			reverse(c.begin(), c.end());
			cout << c << endl;
			return;
		}
		if (j == n)
			j = p[j];
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--)
		solve();
	return 0;
}