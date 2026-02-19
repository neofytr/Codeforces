#include <bits/stdc++.h>
using namespace std;

#define int long long

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

void solve() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}