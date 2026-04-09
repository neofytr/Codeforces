#include <bits/stdc++.h>
using namespace std;

#define int long long

// Calculate phi(n) in O(root(n))
int phi(int n) {
	int res = n;
	for (int r = 2; r * r <= n; r++)
		if (!(n % r)) {
			while(!(n % r))
				n /= r;
			res -= res / r;
		}
	if (n > 1) res -= res / n;
	return res;
}

// Calculate phi(r) for all 1 <= r <= n in O(nlog(log(n)))
vector<int> rangePhi(const int n) {
	vector<int> res(n + 1);
	for (int r = 1; r <= n; r++)
		res[r] = r;

	for (int r = 2; r <= n; r++)
		if (res[r] == r) // prime
			for (int j = r; j <= n; j += r)
				res[j] -= res[j] / r;
	return res;
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

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

int inv(int a, int m) {
	if (gcd(a, m) != 1)
		return  -1;
	return pow(a, phi(m) - 1, m);
}

