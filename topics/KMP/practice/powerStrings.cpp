#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s;
	while (cin >> s, s != ".") {
		int n = s.length();
		vector<int> p(n + 1, 0);

		int j = p[1];
		for (int i = 2; i <= n; i++) {
			while (j > 0 && s[j + 1 - 1] != s[i - 1])
				j = p[j];
			if (s[j + 1 - 1] == s[i - 1])
				j++;
			p[i] = j;
		}

		if (!(n % (n - p[n]))) {
			cout << n / (n - p[n]) << endl;
			continue;
		}

		cout << 0 << endl;
	}
	return 0;
}