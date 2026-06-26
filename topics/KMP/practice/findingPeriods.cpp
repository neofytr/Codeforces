#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s; cin >> s;
	int n = s.length();

	vector<int> p(n + 1, 0); p[0] = -1;
	int j = p[1];
	for (int i = 2; i <= n; i++) {
		while (j > 0 && s[j + 1 - 1] != s[i - 1])
			j = p[j];
		if (s[j + 1 - 1] == s[i - 1])
			++j;
		p[i] = j;
	}

	j = p[n];
	while (j >= 0)
		cout << n - j << " ", j = p[j];
	cout << endl;
	return 0;
}