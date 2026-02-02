#include <bits/stdc++.h>
using namespace std;

#define int long long

int pw(int base, int exp) {
	int res = 1;
	while (exp) {
		if (exp & 1) res = res * base;
		base = base * base;
		exp >>= 1;
	}
	return res;
}

void solve() {
	int n, k; cin >> n >> k;

	int left = 0;
	int right = 19;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (pw(3, mid) <= n) left = mid;
		else right = mid;
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}