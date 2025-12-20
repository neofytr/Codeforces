#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, x, y;
	cin >> n >> x >> y;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	// 1 <= i < j <= n
	// sum - y - arr[j] <= arr[i] <= sum - x - arr[j]

	int cnt = 0;
	multiset<int> ms;
	ms.insert(arr[1]);
	
	for (int j = 2; j <= n; j++) {
		int left = sum - y - arr[j];
		int right = sum - x - arr[j];
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}