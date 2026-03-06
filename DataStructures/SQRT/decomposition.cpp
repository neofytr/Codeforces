#include <bits/stdc++.h>
using namespace std;

int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	int b = sqrt(n);
	
	// The array a is decomposed into n/b + 1 blocks, where the range covered
	// by the ith block is a[(i - 1) * b, min(n, b * i)] for 1 <= i <= n / b + 1
	vector<int> p(n / b + 2, 0);
	for (int i = 1; i <= n / b + 1; i++) 
		for (int j = b * (i - 1) + 1; j <= min(n, b * i); j++)
			p[i] += a[j];

	auto next = [&](int x) {
		// this returns the block number of the first block that starts at index >= x
		int i = (x + b - 1) / b;
	};
	
	int q; cin >> q;
	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int l, r; cin >> l >> r;
		}
	}
	return 0;
}