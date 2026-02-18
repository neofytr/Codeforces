#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)

int pw(int base, int exp) {
	int res = 1;
	base = base % MOD;
	while (exp) {
		if (exp & 1) res = res * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return res;
}


void solve() {
	int n; cin >> n;

	int sum = 0;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r], sum += arr[r];
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}