#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	int val, evensum = 0, oddsum = 0;
	int maxeven = LLONG_MIN, maxodd = LLONG_MIN;
	int oddcnt = 0, evencnt = 0;

	for (int r = 1; r <= n; r++) {
		cin >> val;
		if (val & 1) oddsum += val, maxodd = max(maxodd, val), oddcnt++;
		else evensum += val, maxeven = max(maxeven, val), evencnt++;
	}

	if (maxeven == LLONG_MIN) {
		cout << maxodd << endl;
		return;
	}

	if (maxodd == LLONG_MIN) {
		cout << maxeven << endl;
		return;
	}

	cout << max(maxodd + evensum, (oddsum - oddcnt) + 1ll + evensum) << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}