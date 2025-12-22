#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, q;
	cin >> n >> q;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	unordered_map<int, int> cnt;
	cnt[n - 1] += (arr[2] - arr[1] + 1); // the +1 is arr[n]
	for (int r = 2; r <= n - 1; r++) {
		cnt[r * (n - r)] += (arr[r + 1] - 1 - arr[r]);
		cnt[r * (n - r) + (r - 1)] += 1;
 	}

	int k;
	while (q--) {
		cin >> k;
		cout << cnt[k] << " ";
	}
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}