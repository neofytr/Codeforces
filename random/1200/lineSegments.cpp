#include <bits/stdc++.h>
using namespace std;

#define int long double

void solve() {
	int n;
	cin >> n;

	int px, py, qx, qy;
	cin >> px >> py >> qx >> qy;

	int d = sqrt((px - qx) * (px - qx) + (py - qy) * (py - qy));
	int maxi = d, sum = d, val;
	for (int64_t r = 1; r <= n; r++)
		cin >> val, maxi = max(maxi, val), sum += val;

	if (n == 1) {
		if (d == val)
			cout << "YES\n";
		else 	
			cout << "NO\n";
		return;
	}

	if (2 * maxi <= sum)
		cout << "YES\n";
	else
		cout << "NO\n";
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}