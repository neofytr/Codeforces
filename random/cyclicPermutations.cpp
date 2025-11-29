#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MOD (int)(1e9 + 7)

int pw(int base, int exp) {
	int res = 1;
	base = base % MOD;

	while (exp) {
		if (exp & 1)
			res = res * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return res;
}

int32_t main() {
	int n;
	cin >> n; // 3 <= n <= 1e6

	vector<int> f(n + 1);

	// We count the number of permutations of [1, n] that are not cyclic
	// Now, if n and (n - 1) aren't adjacent, we can always construct a cycle
	// So, we bundle n and (n - 1) together in 2! ways and call this bundle A1
	// Now, if A1 and (n - 2) aren't adjacent, we can always construct a cycle
	// So, we bundle A1 and (n - 2) together in 2! ways and call this bundle A2
	// and so on
	// Thus, the number of permutations of [1, n] that are not cyclic is 2! * 2! * ... * 2! (n - 1) times
	// i.e, 2^(n - 1)

	// So, the number of cyclic permutations of [1, n] is n! - 2^(n - 1)

	f[0] = 1;
	for (int r = 1; r <= n; r++)
		f[r] = r * f[r - 1] % MOD;

	cout << (f[n] - pw(2, n - 1) + MOD) % MOD << endl;
	return 0;
}