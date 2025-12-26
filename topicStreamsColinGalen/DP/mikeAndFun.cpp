#include <bits/stdc++.h>
using namespace std;

#define int long long 


int32_t main() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<vector<int>> mat(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			cin >> mat[r][c];

	vector<vector<int>> dp(n + 1, vector<int>(m + 1));
}