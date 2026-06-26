#include <bits/stdc++.h>
using namespace std;

#define int long long

int res(int l, int r, const string &s) {
	int n = s.length();
	vector<int> p(n + 1);

	p[l] = 0;
	int j = p[l];
	for (int i = l + 1; i <= r; i++) {
		while (j > 0 && s[j + 1 - 1] != s[i - 1])
			j = p[j];
		if (s[j + 1 - 1] == s[i - 1])
			++j;
		p[i] = j;
	}

	int len = r - l + 1;
	if (!((p[r] - len) % len))
		return (p[r] - len);
	return len;
}

int32_t main() {
	string s;
	while (cin >> s, s != "*") {
		int n = s.length();
	}
	return 0;
}