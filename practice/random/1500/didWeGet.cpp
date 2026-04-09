#include <bits/stdc++.h>
using namespace std;

#define N_MAX (26)
#define M_MAX (1000)

int str[M_MAX + 1];
int dp[M_MAX + 1][N_MAX + 1][N_MAX + 1];

void solve(int t) {
	int n, k, m; cin >> n >> k >> m;
	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= n; j++)
			for (int l = 0; l <= k; l++)
				dp[i][j][l] = 0;

	string s; cin >> s;
	for (int i = 1; i <= m; i++)
		str[i] = s[i - 1] - 'a' + 1;

	for (int c = 1; c <= k; c++) dp[0][0][c] = 1;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j <= n; j++)
			for (int c = 1; c <= k; c++)
				dp[i][j][c] = dp[i - 1][j][c];
	
		if (str[i] <= k) {
			for (int j = 1; j <= n; j++) {
				int val = 1;
				for (int l = 1; l <= k; l++)
					val &= dp[i - 1][j - 1][l];
				dp[i][j][str[i]] = val;
			}
	}
}

	bool can = true;
	for (int c = 1; c <= k; c++)
		if (!dp[m][n][c]) {
			can = false;
			break;
		}
	if (can) {
		cout << "YES" << endl;
		return;
	}

	int j = n;
	string res;
	for (int i = m; i >= 1 && j >= 1; i--)
		for (int c = 1; c <= k; c++)
			if (!dp[i][j][c]) {
				j--;
				res.push_back((char)(c + 'a' - 1));
				break;
			}
	while (res.size() < n) res.push_back('a');
	reverse(res.begin(), res.end());
	cout << "NO" << endl;
	cout << res << endl;
}

int32_t main() {
	int t; cin >> t;
	for (int i = 1; i <= t; i++) solve(i);
	return 0;
}