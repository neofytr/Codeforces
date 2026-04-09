#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int x, m;
	cin >> x >> m;

	set<int> res;
	for (int r = 1; r * r <= x; r++)
		if (!(x % r)) {
			int y = r ^ x;
			if (y >= 1 && y <= m && y != x)
				res.insert(y);

			if (r != x / r) {
				y = (x / r) ^ x;
				if (y >= 1 && y <= m && y != x)
					res.insert(y);
			}
		}

	int front = 64 - __builtin_clzll(x);

	for (int y = 1; y <= min((1ll << front) - 1, m); y++) 
		if (x != y && !(y % (x ^ y)))
			res.insert(y);
	
	cout << res.size() << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}