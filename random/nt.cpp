#include <bits/stdc++.h>
using namespace std;

#define int long long 

vector<int> sieve(int n) {
	if (n <= 1)
		return {};

	vector<bool> p(n + 1, true);
	p[0] = p[1] = false;
	for (int r = 2; r * r <= n; r++)
		if (p[r])
			for (int j = r * r; j <= n; j += r)
				p[j] = false;

	return p;
}

// smallest (prime) factor for x >= 2
vector<int> spf(int n) {
	if (n <= 1)
		return {};

	vector<int> p(n + 1, -1);
	for (int r = 2; r <= n; r++)
		if (spf[r] == -1)
			for (int j = r; j <= n; j += r)
				if (spf[j] == -1)
					spf[j] = r;

	return p;
}

#define MAX (int)(1e6)
// fast factorization (log(n))
void fact() {
	int q;
	cin >> q;

	vector<int> sp = spf(MAX);

	int x; // x >= 2
	while(q--) {
		cin >> x;
		while (x != 1) {
			int p = sp[x];
			x /= p;
			cout << p << " ";
		}
		cout << endl;
	}
}

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

int pw(int base, int exp, int mod) {
	int res = 1;
	base = base % mod;

	while(exp) {
		if (exp & 1)
			res = res * base % mod;
		base = base * base % mod;
		exp >>= 1;
	}
	return res;
}

// p is a prime; n > 2 such that it's not divisible by p
// calculate MMI of n mod p (calculated modulo p)
int inv(int n, int p) {
	return pw(n, p - 2, p);
}

// 1 <= r <= n
// calculate C(n, r) % mod
int ncr() {
	int q, mod;
	cin >> q >> mod; // mod is a prime > MAX

	vector<int> f(MAX + 1);
	f[0] = 1;
	for (int r = 1; r <= MAX; r++)
		f[r] = r * f[r - 1] % mod;

	vector<int> invf(MAX + 1);
	invf[MAX] = pw(MAX, mod - 2, mod);
	for (int r = MAX - 1; r >= 0; r--)
		invf[r] = (r + 1) * invf[r + 1] % mod;

	int n, r;
	while(q--) {
		cin >> n >> r;
		cout << (f[n] * invf[r] % mod * invf[n - r] % mod) << endl;
	}
}











































