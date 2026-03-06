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
			for (int i = 0; i < 26; i++) s[i] += k * f[i];
		else
			for (int i = 0; i < 26; i++) t[i] += k * f[i];


		// find the highest character of t
		int ht;
		for (int i = 25; i >= 0; i--)
			if (t[i]) {
				ht = i;
				break;
			}

		if (ht > 0) {
			cout << "YES" << endl;
			continue;
		}

		// now the highest character of t is 0 (a), which is also the 
		// lowest character of s

		// the string t is all a's
		int lens = 0, lent = 0;
		for (int i = 0; i < 26; i++) lens += s[i];
		for (int i = 0; i < 26; i++) lent += t[i];

		if (s[0] == lens) {
			if (lens < lent) {
				cout << "YES" << endl;
			} else cout << "NO" << endl;
			continue;
		}

		// s has a character other than a, t has all its characters a
		cout << "NO" << endl;
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}