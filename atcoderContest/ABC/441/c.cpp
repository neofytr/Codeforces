#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, k, x;
	cin >> n >> k >> x;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];
	sort(arr.begin() + 1, arr.end());

	int sum = 0;
	for (int r = 1; r <= k; r++) sum += arr[r];

	if (sum > x) {
		cout << -1 << endl;
		return 0;
	}
	return 0;
}