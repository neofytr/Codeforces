#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	int sum = 0;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r], sum += arr[r];

	// 1 <= l <= r <= n
	// (r + l)(r - l + 1) - sum[l, r] = max
	// r2 - l2 + r + l - p[r] + p[l - 1]
	// (p[l - 1] - l2 + l) + (r2 + r - p[r]) = max
	
	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + arr[r];

	int maxi = LLONG_MIN, maxival = LLONG_MIN;
	for (int r = 1; r <= n; r++)
		maxi = max(maxi, p[r - 1] - r * r + r), maxival = max(maxival, maxi + r * r + r - p[r]);

	if (maxival <= 0)
		cout << sum << endl;
	else 
		cout << sum + maxival << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}