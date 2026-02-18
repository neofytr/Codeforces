#include <bits/stdc++.h>
using namespace std;

#define int long long

#define p(r, k) (((k) - 1) * (r) + ((r) * ((r) + 1)) / 2)

void solve() {
	int n, k;
	cin >> n >> k;

	int mini = LLONG_MAX;
	int t = p(n, k);
	int left = 0;
	int right = n;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (2 * p(mid, k) <= t) left = mid;
		else right = mid;
	}

	mini = min(mini, abs(2 * p(left, k) - t));

	left = 0;
	right = n;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (2 * p(mid, k) >= t) right = mid;
		else left = mid;
	}

	mini = min(mini, abs(2 * p(right, k) - t));
	cout << mini << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}