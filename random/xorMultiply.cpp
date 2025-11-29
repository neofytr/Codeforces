#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, a, b;
	cin >> n >> a >> b;

	int alpha = 0, beta = 0;
	int x = max(a, b), y = min(a, b);

	bool first = false;
	for (int bit = n - 1; bit >= 0; bit--) {
		int mask = 1ll << bit;
		if ((x & mask) && (y & mask))
			alpha |= mask, beta |= mask;
		else if (!(x & mask) && !(y & mask))
			alpha |= mask, beta |= mask;
		else {
			if (!first) 
				alpha |= mask, first = true;
			else 
				beta |= mask;
		}
	}
	cout << (alpha ^ x) << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}