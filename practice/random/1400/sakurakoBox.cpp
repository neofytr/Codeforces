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
		cin >> arr[r], sum = (sum + arr[r]) % MOD;

	int res = 0;
	for (int r = 1; r <= n; r++) 
		res = (res + arr[r] * sum % MOD - arr[r] * arr[r] % MOD + MOD) % MOD;
	
	int inv = pw(n * (n - 1), MOD - 2);
	cout << res * inv % MOD << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}