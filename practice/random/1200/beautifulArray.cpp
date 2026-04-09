#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int a, b;
	cin >> a >> b;

	// b - m b b + r

	// (3b + r - m) / 3 = a 
	// (r - m) / 3  = a - b
	// r - m = 3 * (a - b)
	// m = 1
	// r = 3 * (a - b) + 1
	int m = max((b - a) * 3 + 1, 1ll);
	int r = 3 * (a - b) + m;

	cout << 3 << endl;
	cout << b - m << " " << b << " " << b + r << endl;
	return 0;
}