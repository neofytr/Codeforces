#include <bits/stdc++.h>
using namespace std;

#define int long long 

int pw(int base, int exp) {
	int res = 1;
	while(exp) {
		if (exp & 1)
			res = res * base;
		base = base * base;
		exp >>= 1;
	}
	return res;
}

int32_t main() {
	int x;
	cin >> x;

	map<int, int> prime;
	for (int r = 2; r * r <= x; r++)
		while(!(x % r))
			prime[r]++, x /= r;
	if (x > 1) prime[x]++;

	int mini = LLONG_MAX;
	int minia;

	int c = prime.size();
	for (int subset = 0; subset < (1LL << c); subset++) {
		int a = 1;
		int b = 1;

		int bit = 0;
		for (auto &[p, cnt] : prime) {
			if (subset & (1LL << bit))
				a *= pw(p, cnt);
			else 
				b *= pw(p, cnt);
			bit++;
		}
			
		int m = max(a, b);
		if (m <= mini) {
			mini = m;
			minia = min(a, b);
		}
	}

	cout << minia << " " << mini << endl;
	return 0;
}