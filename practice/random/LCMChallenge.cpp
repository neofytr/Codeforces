#include <bits/stdc++.h>
using namespace std;

#define int long long 

// a 2p1 3p2 5p3 ...
// b 2q1 3q2 5q3 ...
// c 2r1 2r2 5r3 ...
// l 2max(p1, q1, r) * 3max(p2, q2, r2) ...

int32_t main() {
	int n;
	cin >> n;

	if (n == 1 || n == 2) {
		cout << n << endl;
		return 0;
	}

	// Let n >= 3
	// LCM of any three numbers in the range [1, n] <= n * (n - 1) * (n - 2)

	// If n is odd, lcm(n, n - 1, n - 2) = n * (n - 1) * (n - 2) since they
	// have no prime factors in common

	// If n is even (n >= 4), then maxLCM >= (n - 1) * (n - 2) * (n - 3) since
	// lcm(n - 1, n - 2, n - 3) = (n - 1) * (n - 2) * (n - 3)
	if (n & 1)
		cout << n * (n - 1) * (n - 2);
	else {
		int maxi = (n - 1) * (n - 2) * (n - 3);
		for (int r = 1; r <= n; r++) {
			maxi = max(maxi, lcm(lcm(n, n - 1), r));
			maxi = max(maxi, lcm(lcm(n, n - 2), r));
			maxi = max(maxi, lcm(lcm(n, n - 3), r));
		}
		cout << maxi;
	}
	cout << endl; 
	return 0;
}