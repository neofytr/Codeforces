#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, k;
	cin >> n >> k;

	int packs = LLONG_MAX;
	for (int r = 1; r * r <= n; r++)
		if (!(n % r)) {
			if (r <= k)
				packs = min(packs, n / r);
			if (n / r <= k)
				packs = min(packs, r);
		}
	cout << packs << endl;
}

int32_t main() {
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}