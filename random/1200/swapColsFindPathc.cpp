#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<vector<int>> arr(3, vector<int>(n + 1));
	for (int r = 1; r <= 2; r++)
		for (int c = 1; c <= n; c++)
			cin >> arr[r][c];

	pair<int, int> maxi = {LLONG_MIN, -1};
	for (int r = 1; r <= n; r++)
		if (arr[1][r] + arr[2][r] > maxi.first)
			maxi.first = arr[1][r] + arr[2][r], maxi.second = r;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}