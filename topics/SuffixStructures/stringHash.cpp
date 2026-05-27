#include <bits/stdc++.h>
using namespace std;

#define int long long

const int p = 911382323;
const int MOD = (int)(1e9) + 7;

// Let s[1, n] is a string of lowercase latin characters (which are mapped to the range [1, 26])
// Let pw[i] = p^i % MOD for i >= 0

// hash(s) = summation (1 <= i <= n) s[i] * pw[i - 1] % MOD
// hash[i] = summation (1 <= r <= i) s[i] * pw[i - 1] % MOD
// hash(s[l, r]) = inv(pw[l - 1], MOD) * ((h[r] - h[l - 1]) % MOD);

int pow(int base, int exp) {
	int res = 1;
	while (exp) {
		if (exp & 1)
			res = res * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return res;
}

int32_t main() {
	string s; cin >> s;
	int n = s.length();

	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++)
		str[i] = s[i - 1] - 'a' + 1;

	vector<int> pw(n + 1), ipw(n + 1);
	pw[0] = ipw[0] = 1;
	for (int i = 1; i <= n; i++)
		pw[i] = (pw[i - 1] * p) % MOD, ipw[i] = pow(p[i], MOD - 2);

	vector<int> hash(i + 1, 0);
	for (int i = 1; i <= n; i++)
		hash[i] = (hash[i - 1] + str[i] * pw[i - 1]) % MOD;

	auto get_substr_hash = [&] (int l, int r) {
		return ipw[l - 1] * ((hash[r] - hash[l - 1] + MOD) % MOD) % MOD;
	};
	return 0;
}

