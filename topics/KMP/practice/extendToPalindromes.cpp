#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s;
	while (cin >> s) {
		int n = s.length();
		int r = n - 1;
		int l = 0;

		int first = -1;
		while (l <= r && l <= n - 1) {
			if (l <= n - 1 && s[l] != s[r]) {
				l++; continue;
			}

			first = l;
			l++, r--;
		}

		if (r == n - 1) {
			string t = s;
			reverse(t.begin(), t.end());
			cout << s << t << endl;
		}

		if (s[r + 1] == s[l - 1]) {
			string t = s.substr(0, first);
			reverse(t.begin(), t.end());
			cout << s << t << endl;
		}
	}
	return 0;
}