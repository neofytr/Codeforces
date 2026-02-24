#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	sort(arr.begin() + 1, arr.end());
	int l = 1, r = n;

	int cnt = 0;
	while (l <= r) {
		if (l == r) {
			cnt += (arr[l] + 1) / 2;
			break;
		}

		int sum = 0;
		while (l <= r && sum < arr[r]) sum += arr[l++];
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}