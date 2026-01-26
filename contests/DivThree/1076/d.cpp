#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e16)

void solve() {
	int n;
	cin >> n;

	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	vector<int> maxpsbl(n + 1, -INF); // maxpsbl[r] is the
	// maximum possible value of x that can clear the first r levels

	int sum = 0;
	sort(a.begin() + 1, a.end());
	for (int r = 1; r <= n; r++) {
		sum += b[r]; // sum is the total number of sword strikes
		// required to clear the first r levels
		if (sum <= n) 
			maxpsbl[r] = a[n - sum + 1];
	}

	int maxi = -INF;
	for (int r = 1; r <= n; r++)
		if (maxpsbl[r] != -INF)
			maxi = max(maxi, r * maxpsbl[r]);

	cout << max(0ll, maxi) << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}