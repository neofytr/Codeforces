#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, x, y;
	cin >> n >> x >> y;

	int sum = 0;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r], sum += arr[r];

	// 1 <= i < j <= n
	// sum - y - arr[j] <= arr[i] <= sum - x - arr[j]

	// sum - y <= arr[i] + arr[j] <= sum - x

	sort(arr.begin() + 1, arr.end());
	vector<int> v;
	v.push_back(arr[1]);
	int cnt = 0;
	for (int j = 2; j <= n; j++) {
		int left = sum - y - arr[j];
		int right = sum - x - arr[j];

		auto leftitr = lower_bound(v.begin(), v.end(), left);
		if (leftitr != v.end()) {
			auto rightitr = lower_bound(v.begin(), v.end(), right + 1);
			cnt += rightitr - leftitr;
		}

		v.push_back(arr[j]);
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}