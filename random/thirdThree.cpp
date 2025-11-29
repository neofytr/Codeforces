#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	// 1 <= n <= 1e9
	// Find 0 <= a, b, c <= 1e9 such that
	// (a ^ b) + (b ^ c) + (c ^ a) = n, or determine that there are 
	// no such integers (print -1 in this case)

	if (n & 1) {
		cout << -1 << endl;
	} else {
		cout << 0 << " " << n / 2 << " " << n / 2 << endl;
	}
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}