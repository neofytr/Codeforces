#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> arr(n + 1), ones(n + 1, 0);
	for (int r = 1; r <= n; r++) cin >> arr[r];
	for (int r = 1; r <= n; r++)
		ones[r] = ones[r - 1] + (arr[r] == 1 ? 1 : 0);

	int mini = LLONG_MAX;
	for (int l = 1; l <= n; l++) {
		int g = arr[l];
		int r = l;
		while (r <= n && g != 1)
			g = gcd(g, arr[r]), r++;
		if (l != r)
			r--;

		// [l, r]
		if (r <= n && g == 1) {
			int cost = 2 * (r - l) + (n - r) - (ones[n] - ones[r]) + (l - 1) - ones[l - 1];
			mini = min(mini, cost);
		}
	}

	cout << (mini == LLONG_MAX ? -1 : mini) << endl;
	return 0;	
}