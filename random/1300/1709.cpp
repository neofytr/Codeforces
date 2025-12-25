#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	vector<pair<int, int>> ops;
	for (int r = 1; r <= n; r++)
		if (a[r] > n)
			swap(a[r], b[r]), ops.push_back({3, r});

	bool done = true;
	while (done) {
		done = false;
		for (int r = 1; r <= n - 1; r++)
			if (a[r + 1] < a[r])
				done = true, swap(a[r + 1], a[r]), ops.push_back({1, r});
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
}