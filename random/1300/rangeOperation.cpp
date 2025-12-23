#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	// Find the subarray arr[l, r], where 1 <= l <= r <= n such that
	// (l + r) - sum[l, r] is maximized, i.e, (l + r) - (p[r] - p[l - 1]) is maximized
	// (l - 1 - p[l - 1]) + (r - p[r]) + 1 is maximized
	// ((l - 1) - p[l - 1]) + (r - p[r]) is maximized

	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + arr[r];

	int maxi = LLONG_MIN;
	int prevm = (1 - 1) - p[1 - 1];
	for (int r = 1; r <= n; r++)
		prevm = max(prevm, r - p[r]), maxi = max(maxi, prevm + r - p[r]);

	maxi++;
	if (maxi >= 0) 
		cout << p[n] + maxi << endl;
	else 
		cout << p[n] << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}