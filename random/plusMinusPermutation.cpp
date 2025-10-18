#include <bits/stdc++.h>
using namespace std;

#define int long long 

int _lcm(int x, int y) {
	return (x * y) / gcd(x, y);
}

int32_t main() {
	int t;
	cin >> t;
	while(t--) {
		int n, x, y;
		cin >> n >> x >> y;

		int r1 = n / x  - n / _lcm(x, y);
		int r2 = n / y - n / _lcm(x, y);

		cout << (n * (n + 1)) / 2 - ((n - r1) * (n - r1 + 1)) / 2 - (r2 * (r2 + 1)) / 2 << endl;
	}
	return 0;
}