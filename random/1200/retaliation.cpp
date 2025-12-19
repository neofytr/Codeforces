#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int64_t n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int64_t r = 1; r <= n; r++) cin >> arr[r];

	int num = 2 * arr[1] - arr[2];	
	if (num < 0 || (num % (n + 1))) {
		cout << "NO\n";
		return;
	}

	int beta = num / (n + 1);
	int alpha = arr[1] - beta * n;

	if (alpha < 0) {
		cout << "NO\n";
		return;
	}

	for (int r = 3; r <= n; r++)
		if (arr[r] != (alpha * r + beta * (n - r + 1))) {
			cout << "NO\n";
			return;
		}

	cout << "YES\n";
}

int32_t main() {
	int64_t t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}