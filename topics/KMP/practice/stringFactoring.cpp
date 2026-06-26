#include <bits/stdc++.h>
using namespace std;

#define int long long

int res(int l, int r, const string &s) {
	int n = s.length();
	vector<int> p(n + 1);

	p[l] = 0;
	int j = p[l];
	for (int i = l + 1; i <= r; i++) {
		while (j > 0 && s[l + j - 1] != s[i - 1])
			j = p[j];
		if (s[l + j - 1] == s[i - 1])
			++j;
		p[i] = j;
	}

	int len = r - l + 1;
	int period = len - p[r];
	return period + len % period;
}

int32_t main() {
	string s;
	while (cin >> s, s != "*") {
		int n = s.length();

		// dp[r] is the minimal weight for s[1, r]
		vector<int> dp(n + 1, LLONG_MAX);
		dp[0] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= i; j++)
				dp[i] = min(dp[i], res(j, i, s) + dp[j - 1]);

		
		cout << dp[n] << endl;
		cout << res(3, 9, s) << endl;
	}
	return 0;
}