#include <bits/stdc++.h>
using namespace std;

#define int long long 

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