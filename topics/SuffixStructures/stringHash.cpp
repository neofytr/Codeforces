#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(3 * 1e5)

#define substr_hash(l, r, hash) ((ipw[(l) - 1]) * ((hash[r] - hash[l - 1] + MOD) % MOD) % MOD) 

const int p = 33;
const int MOD = (int)(1e9) + 7;

int pw[MAX + 1], ipw[MAX + 1];

// Let s[1, n] is a string of lowercase latin characters (which are mapped to the range [1, 26])
// Let pw[i] = p^i % MOD for i >= 0

// hash(s) = summation (1 <= i <= n) s[i] * pw[i - 1] % MOD
// hash[i] = summation (1 <= r <= i) s[i] * pw[i - 1] % MOD
// hash(s[l, r]) = inv(pw[l - 1], MOD) * ((h[r] - h[l - 1]) % MOD);

vector<int> get_hash(string &s) {
	int n = s.length();
	vector<int> hash(n + 1);
	hash[0] = 0;
	for (int i = 1; i <= n; i++)
		hash[i] = (hash[i - 1] + (s[i - 1] - 'a' + 1) * pw[i - 1]) % MOD;
	return hash;
}

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
	string s, t; cin >> s >> t;
	int n = s.length();
	int m = t.length();

	pw[0] = ipw[0] = 1;
	for (int i = 1; i <= max(n, m); i++)
		pw[i] = (pw[i - 1] * p) % MOD, ipw[i] = pow(pw[i], MOD - 2);	

	// We want to compare s and t by first computing its LCP in log(min(n, m)) 
	// and then using its LCP to do the comparison in O(1)

	vector<int> hash_s = get_hash(s), hash_t = get_hash(t);

	int left = 1;
	int right = min(n, m);

	int lcp = 0;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (substr_hash(1, mid, hash_s) == substr_hash(1, mid, hash_t))
			lcp = mid, left = mid + 1;
		else
			right = mid - 1;
	}

	if (lcp == min(n, m))
		if (n == m) {
			cout << 0 << endl;
			return 0;
		}
		else if (n < m) {
			cout << -1 << endl;
			return 0;
		} else {
			cout << 1 << endl;
			return 0;
		}

	if (s[lcp] < t[lcp])
		cout << -1 << endl;
	else
		cout << 1 << endl;
	return 0;
}

