#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	int sum = 0;
	vector<vector<int>> g(n + 1, vector<int>(n + 1));
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= n; col++)
			cin >> g[row][col], sum += g[row][col];

	int maxi = LLONG_MIN;
	for (int i = 1; i <= n; i++)
		maxi = max(maxi, sum - g[i][n + 1 - i]);
	cout << maxi << endl;
	return 0;
}