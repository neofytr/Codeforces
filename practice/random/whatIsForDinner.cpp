#include <bits/stdc++.h>
using namespace std;

#define int long long 

// row 1 -> 1 (13)
// row 2 -> 2

int32_t main() {
	int n, m, k;
	cin >> n >> m >> k;

	int r;
	vector<vector<int>> row(m + 1);
	vector<int> viability(n + 1);
	for (int tooth = 1; tooth <= n; tooth++) 
		cin >> r >> viability[tooth], row[r].push_back(tooth);

	int res = 0;
	for (int r = 1; r <= m; r++) {
		int mini = LLONG_MAX;
		for (int t : row[r])
			mini = min(mini, viability[t]);
		res += mini;
	}

	cout << min(res, k) << endl;
	return 0;
}