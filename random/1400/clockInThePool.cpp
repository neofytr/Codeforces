#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int k, m; cin >> k >> m;
	int a = m / k, r = m % k;
	if (!(a % 3))
		cout << 2 * k - r << endl;
	else if (a % 3 == 1)
		cout << k - r << endl;
	else cout << 0 << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}