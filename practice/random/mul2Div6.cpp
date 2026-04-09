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

void solve() {
	int n;
	cin >> n;

	int x = n;

	int one = 0;
	int two = 0;

	while(!(n % 2))
		one++, n /= 2;

	while(!(n % 3))
		two++, n /= 3;

	if (two < one) {
		cout << -1 << endl;
		return;
	}

	if (x / (pw(2, one) * pw(3, two)) > 1) {
		cout << -1 << endl;
		return;
	}

	cout << 2 * two - one << endl;
	return;
} 

int32_t main() {
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}