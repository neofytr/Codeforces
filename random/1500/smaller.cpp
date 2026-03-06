#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int q; cin >> q;

	vector<int> s(26, 0), t(26, 0);
	s[0] = t[0] = 1;
	while (q--) {
		int d, k; cin >> d >> k;
		string str; cin >> str;
		vector<int> f(26, 0);
		for (char c : str)
			f[c - 'a']++;

		if (d == 1)
			for (int i = 0; i < 26; i++) s[i] += f[i];
		else
			for (int i = 0; i < 26; i++) t[i] += f[i];

		int c = 0;
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}