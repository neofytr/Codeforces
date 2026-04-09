#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	if (n == 1) {
		cout << arr[1] << endl;
		return;
	}

	if (n == 2) {
		cout << max(arr[2] - arr[1], max(arr[1] - arr[2], arr[1] + arr[2])) << endl;
		return;
	}

	vector<vector<int>> C(n + 1, vector<int>(n + 1));
	C[0][0] = 1;
	for (int r = 1; r <= n; r++) {
		C[r][0] = 1;
		for (int s = 1; s <= r; s++)
			C[r][s] = C[r - 1][s] + C[r - 1][s - 1];
	}

	int maxi = 0;
	for (int r = 1; r <= n; r++) maxi += arr[r];

	for (int op = 0; op <= n - 1; op++) {
		int last = 0;
		int sign = 1;
		for (int r = 0; r <= op; r++)
			last += sign * C[op][r] * arr[n - r], sign *= -1;
		int first = 0;
		sign = 1;
		for (int r = 0; r <= op; r++)
			first += sign * arr[op + 1 - r] * C[op][r], sign *= -1;
		maxi = max(maxi, max(last - first, first - last));
	}

	cout << maxi << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}