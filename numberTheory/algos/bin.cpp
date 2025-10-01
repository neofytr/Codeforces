#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)
#define MAX (1000000)

int pw(int base, int exp) {
	int res = 1;
	while(exp) {
		if (exp & 1)
			res = res * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return res;
}

int32_t main() {
	int q;
	cin >> q;

	vector<int> fact(MAX + 1);
	vector<int> invFact(MAX + 1);

	fact[0] = 1;
	for (int r = 1; r <= MAX; r++)
		fact[r] = (fact[r - 1] * r) % MOD;

	invFact[MAX] = pw(fact[MAX], MOD - 2);
	for (int r = MAX - 1; r >= 0; r--)
		invFact[r] = ((r + 1) * invFact[r + 1]) % MOD;

	while(q--) {
		// 0 <= r <= n < MAX and n != 0
		int n, r;
		cin >> n >> r;

		int ncr = fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
		cout << ncr << endl;
	}
	return 0;
}