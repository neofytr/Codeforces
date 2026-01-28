#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define MOD (int)(1e9 + 7)

int fact[MAX + 1];
int invFact[MAX + 1];
int dp[MAX + 1];
int p[MAX + 1];

int C(int n, int r) {
	if (r > n) return 0;
	return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

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


int32_t main() {
	fact[0] = 1;
	for (int r = 1; r <= MAX; r++)
		fact[r] = (r * fact[r - 1]) % MOD;
	invFact[MAX] = pw(fact[MAX], MOD - 2);
	for (int r = MAX - 1; r >= 0; r--)
		invFact[r] = ((r + 1) * invFact[r + 1]) % MOD;

	int t, k;
	cin >> t >> k;

	dp[0] = 1;
	for (int r = 1; r <= MAX; r++) {
	    dp[r] = dp[r - 1];
	    if (r >= k)
	        dp[r] = (dp[r] + dp[r - k]) % MOD;
	}
	
	p[0] = 0;
	for (int r = 1; r <= MAX; r++)
		p[r] = (p[r - 1] + dp[r]) % MOD;

	int a, b;
	while (t--) {
		cin >> a >> b;
		cout << (p[b] - p[a - 1] + MOD) % MOD << endl;
	}

	return 0;
}