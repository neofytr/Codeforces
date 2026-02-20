#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;

	vector<int> arr(n + 1);
	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r], b[r] = arr[r];


	sort(arr.begin() + 1, arr.end());
	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + arr[r];

	auto can = [&arr, &p, &n, &k](int x) -> bool {
		int idx = lower_bound(arr.begin() + 1, arr.end(), x) - arr.begin();
		idx--;
		return idx * x - p[idx] <= k;
	};

	int left = 0;
	int right = arr[n] + k + 1;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid)) left = mid;
		else right = mid;
	}

	int res = n * (left - 1) + 1;
	int cnt = 0;
	int used = 0;
	for (int r = 1; r <= n; r++)
		if (b[r] <= left) used += left - b[r];
		else cnt++;

	cout << res + cnt + (k - used) << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}