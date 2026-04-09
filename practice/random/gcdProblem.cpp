#include <bits/stdc++.h>
using namespace std;

#define int long long 

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

void solve() {
	int n;
	cin >> n;

	if (n & 1) {
		for (int a = 2; a <= n - 1; a++) {
			int b = n - 1 - a;
			if ((b != 1 && b != a && b >= 1) && gcd(a, b) == 1) {
				cout << a << " " << b << " " << 1 << endl;
				return;
			}
		}
	} else {
		cout << n / 2 << " " << n / 2 - 1 << " " << 1 << endl;
	}
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}