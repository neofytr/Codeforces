#include <bits/stdc++.h>
using namespace std;

#define int long long 

// Let pi(n) is the number of primes in the range [1, n] for n >= 1
// pi(n) is O(n / log(n))

// The number of divisors of n is O(n^(1 / 3)) for n >= 1

// All positive factors of n in O(root(n))
vector<int> factors(const int n) {
	vector<int> res;
	if (n <= 0)
		return res;

	for (int r = 1; r * r <= n; r++)
		if (!(n % r))
			res.push_back(r), r != n / r && res.push_back(n / r);
	return res;
}

// Divisors of all numbers in the range [1, n] in O(nlog(n)) for n >= 1
vector<vector<int>> divisors(const int n) {
	if (n <= 0)
		return {};

	// res[r] contains all the divisors of r for 1 <= r <= n
	vector<vector<int>> res(n + 1);
	for (int r = 1; r <= n; r++)
		for (int j = r; j <= n; j += r)
			res[j].push_back(r);
	return res;
}

// Prime factorization of n in O(root(n))
vector<int> primeFactorization(const int n) {
	vector<int> res;
	if (n <= 1)
		return res; 

	for (int r = 2; r * r <= n; r++)
		while(!(n % r))
			res.push_back(r), n /= r;
	if (n > 1) res.push_back(r);
	return res;
}

// Prime factorization of x in O(log(x)) with O(max_xlog(max_x)) precomputation
void primeFactorizationTwo(int max_x, int q) {
	// dp[r] is the smallest (prime) factor of r for r >= 2
	vector<int> dp(max_x + 1, -1);
	for (int r = 2; r <= max_x; r++)
		for (int j = r; j <= max_x; j += r)
			if (dp[j] == -1)
				dp[j] = r;

	while(q--) {
		int x;
		cin >> x;

		int p;
		while(x != 1) 
			p = dp[x], cout << p << " ", x /= p;
		cout << "\n";
	}
}

// Number of factors of x in O(log(x)) with O(max_xlog(max_x)) precomputation
void numFactors(int max_x, int q) {
	// dp[r] is the smallest (prime) factor of r for r >= 2
	vector<int> dp(max_x + 1, -1);
	for (int r = 2; r <= max_x; r++)
		for (int j = r; j <= max_x; j += r)
			if (dp[j] == -1)
				dp[j] = r;

	while(q--) {
		int x;
		cin >> x;

		int p, cnt;
		int res = 1;
		while(x != 1) {
			cnt = 0, p = dp[x]; 
			while(!(x % p))
				cnt++, x /= p;
			res *= (cnt + 1);
		}
		cout << res << endl;;
	}
}

vector<bool> sieve(const int n) {
	// prime[r] is true if r is a prime and false otherwise; for 2 <= r <= n
	vector<bool> prime(n + 1, true);
	if (n <= 0)
		return prime;
	for (int r = 2; r * r <= n; r++)
		if (prime[r])
			for (int j = r * r; j <= n; j += r)
				prime[j] = false;
	return prime;
}

int pow(int base, int exp, int m) {
	int res = 1;
	base = base % m;
	while(exp) {
		if (exp & 1)
			res = res * base % m;
		base = base * base % m;
		exp >>= 1;
	}
	return res;
}

int x, y;
int extendedGCD(const int a, const int b) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}

	int g = extendedGCD(b, a % b);
	int xdash = x, ydash = y;

	x = ydash;
	y = xdash - (a / b) * ydash;
	return g;
}

// Returns the MMI of w modulo m if it exists; returns -1 otherwise
// This exists iff gcd(w, m) = 1
int modInv(const int w, const int m) {
	if (extendedGCD(w, m) != 1)
		return -1;
	int inv = x % m;
	if (inv < 0)
		inv += m;
	return inv;
}

int gcd(const int a, const int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

int lcm(const int a, const int b) {
	return (a / gcd(a, b)) * b; // this may prevent some overflows
}