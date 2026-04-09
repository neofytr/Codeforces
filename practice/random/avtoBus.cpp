#include <bits/stdc++.h>
using namespace std;

#define int long long 

// n >= 1

// Maximize s = x + y under the constraints that x, y >= 0 are integers such that 4 * x +  6 * y = n;

// There exist non-negative integers x, y such that 4 * x + 6 * y = n iff 2 | n
// So, let n = 2 * m for some m >= 1

// So, 2 * x + 3 * y = m for some non-negative integers x, y
// 2 * x = m - 3 * y
// Thus, 2 | (m - 3 * y), or both m and y have the same parity
// x = (m - 3 * y) / 2

// Now, s = x + y = (m - y) / 2
// y >= 0
// Now, x >= 0 -> m >= 3y and m and y have the same parity
// So, y <= floor(m / 3) and m, y have the same parity

// So 0 <= y <= floor(m / 3) and m, y have the same parity


void solve() {
	int n;
	cin >> n;

	if (n & 1) {
		cout << -1 << endl;
		return;
	}

	int m = n / 2;
	if (!(m & 1)) {
		int f = m / 3;

		int maxi = m / 2, mini;
		if (!(f & 1))
			mini = (m - f) / 2;
		else
			mini = (m - f + 1) / 2;
		cout << mini << " " << maxi << endl;
	} else if (m == 2) {
		cout << -1 << endl;
	} else if (m == 3) {
		cout << 1 << " " << 1 << endl;
	} else if (m == 1) {
		cout << -1 << endl;
	} else {
		int f = m / 3;
		int maxi = (m - 1) / 2, mini;

		if (!(f & 1))
			mini = (m - f + 1) / 2;
		else 
			mini = (m - f) / 2;
		cout << mini << " " << maxi << endl;
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