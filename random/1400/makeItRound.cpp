#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(1e3)

int pw(int base, int exp) {
	int res = 1;
	while (exp) {
		if (exp & 1) 
			res = res * base;
		base = base * base;
		exp >>= 1;
	}
	return res;
}

void solve() {
	int n, m;
	cin >> n >> m;
	
	int nc = n;
	vector<int> fact(100, 0);
	for (int r = 2; r * r <= nc; r++) 
		while (!(nc % r))
			nc /= r, fact[r]++;
	if (nc > 1) fact[nc]++;

	int x = fact[2], y = fact[5];
	if (x < y) {
		if (pw(2, y - x) >= m) {
			cout << n * m << endl;
			return;
		}
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}