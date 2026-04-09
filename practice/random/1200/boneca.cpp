#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	int maxi = LLONG_MIN;
	vector<int> arr(n + 1), bit(30);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	for (int r = 1; r <= n; r++)
		for (int b = 0; b <= 29; b++)
			if (arr[r] & (1ll << b))
				bit[b]++;

	for (int r = 1; r <= n; r++) {
		int res = 0;
		for (int b = 0; b <= 29; b++)
			if (arr[r] & (1ll << b))
				res += (n - bit[b]) * (1ll << b);
			else
				res += bit[b] * (1ll << b);
		maxi = max(res, maxi);
	}

	cout << maxi << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}