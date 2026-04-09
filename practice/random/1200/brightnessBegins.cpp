#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int k;
	cin >> k;

	// The problem can be restated as:
	// Find the smallest positive integer n such that the number
	// of numbers <= n having even number of divisors = k 

	// Any number r >= 1 has an even number of divisors unless it is
	// a perfect square of a positive integer

	// If we have r perfect squares in the range [1, n], then, n - r = k
	// r = floor(root(n))

	// Find the smallest positive integer n such that n - floor(root(n)) = k

	int left = 0;
	int right = 2 * k + 1;
	int res = LLONG_MAX;

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		int m = mid - (int)sqrtl(mid);
		if (m < k)
			left = mid;
		else if (m > k)
			right = mid;
		else 
			right = mid, res = min(res, mid);
	}

	cout << res << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}