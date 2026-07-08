#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s;
	while (cin >> s) {
		int n = s.length();
		string t = s; reverse(t.begin(), t.end());
		vector<int> p(n + 1, 0);

		int j = p[1];
		for (int i = 2; i <= n; i++) {
			while (j > 0 && t[j + 1 - 1] != t[i - 1])
				j = p[j];
			if (t[j + 1 - 1] == t[i - 1])
				++j;
			p[i] = j;
		}

		j = 0;
		int want = LLONG_MAX;
		for (int i = 1; i <= n; i++) {
			while (j > 0 && t[j + 1 - 1] != s[i - 1])
				j = p[j];
			if (t[j + 1 - 1] == s[i - 1])
				++j;

			int left = n - i + 1;
			if (left == j || j + 1 == left)
				want = min(want, i - j);
		}

		string k = s.substr(0, want); reverse(k.begin(), k.end());
		cout << s + k << endl;
	}
	return 0;
}