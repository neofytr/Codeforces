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

	int upsum = 0, downsum = 0;
	for (int r = 1; r <= n; r++)
		if (maxi.second != r)
			upsum += arr[1][r], downsum += arr[2][r];

	int upg2 = 0, downg1 = 0;
	for (int r = 1; r <= n; r++)
		if (maxi.second != r)
			if (arr[1][r] <= arr[2][r]) upg2 += arr[1][r];
			else downg1 += arr[2][r];

	cout << maxi.first << endl;
	cout << upsum << endl;
	cout << downsum << endl;

	cout << maxi.first + upsum + downsum - upg2 - downg1 << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}