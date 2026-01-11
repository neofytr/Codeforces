#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> table(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			cin >> table[r][c];

	vector<vector<int>> dp(n + 1, vector<int>(m + 1));
	for (int c = 1; c <= m; c++) {
		dp[1][c] = 1;
		for (int r = 2; r <= n; r++)
			if (table[r][c] >= table[r - 1][c])
				dp[r][c] = dp[r - 1][c] + 1;
			else dp[r][c] = 1;
	}

	vector<set<int>> s(n + 1);
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			s[r].insert(dp[r][c]);

	int k, l, r;
	cin >> k;
	while (k--) {
		cin >> l >> r;
		int len = r - l + 1;
		if (s[r].lower_bound(len) != s[r].end())
			cout << "Yes" << endl;
		else 
			cout << "No" << endl;
	}
	return 0;
}