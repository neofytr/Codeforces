#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> a[r] >> b[r];

	auto can = [&](int x) {
		// can we invite atleast x people
		// [a1, ..., ax] where 1 <= a1 < .. < ax <= n
		// r - 1 <= b[ar] and x - r <= a[ar]

		int r = 1;
		for (int idx = 1; idx <= n; idx++) 
			if (b[idx] >= r - 1 && x - r <= a[idx])
				r++;
		return (r - 1) >= x;
	};

	int left = 0;
	int right = n + 1;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid))
			left = mid;
		else 
			right = mid;
	}

	cout << left << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}