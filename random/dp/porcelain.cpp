#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define NMAX (int)(1e2)
#define INF (int)(1e8)
#define MMAX (int)(1e4)

int dp[NMAX + 1][MMAX + 1];

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	cin >> n >> m;

	int sz;
	vector<vector<int>> mat(n + 1);
	for (int r = 1; r <= n; r++) {
		cin >> sz;
		mat[r].resize(sz + 1, 0);
		for (int c = 1; c <= sz; c++)
			cin >> mat[r][c];
	}

	vector<vector<int>> p(n + 1);
	for (int r = 1; r <= n; r++) {
		sz = mat[r].size() - 1;
		p[r].resize(sz + 1, 0);

		p[r][0] = 0;
		for (int c = 1; c <= sz; c++)
			p[r][c] += p[r][c - 1] + mat[r][c];
	}


	vector<vector<int>> maxi(n + 1);
	for (int r = 1; r <= n; r++) {
		sz = mat[r].size() - 1;
		maxi[r].resize(sz + 1, 0);

		for (int alpha = 0; alpha <= sz; alpha++) {
			maxi[r][alpha] = LLONG_MIN;
			for (int l = 0; l <= alpha; l++)
				maxi[r][alpha] = max(maxi[r][alpha], p[r][l] + p[r][sz] - p[r][sz - alpha + l]);
		}
	}

	// dp[i][j] is the maximal total value of tantrum for the first i rows with a total of
	// j shrieks
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			dp[i][j] = -INF;

	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = 0;
		for (int j = 1; j <= m; j++) {
			int sz = mat[i].size() - 1;
			for (int k = 0; k <= min(sz, j); k++)
				dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + maxi[i][k]);
		}
	}

	cout << dp[n][m] << endl;
	return 0;
}