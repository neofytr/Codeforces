#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, d;
	cin >> n >> d;

	// arr[1, n] is strictly increasing
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	// A segment [l, r] is good iff arr[r] - arr[l] <= d
	// Subsegment monotonic

	// Consider the largest good segment ending at r for some 1 <= r <= n, say [l, r]
	// Then for any collection of distinct points {x, y, z} which has r in it
	// has the rest of its points in the range [l, r - 1] if r >= 2
	// Also r - l >= 2 for there two be atleast two points in [l, r - 1] to choose from
	// Since l >= 1, r - l >= 3 ensure r >= 3 and thus r >= 2
	// If r <= 2, then no such collection exists

	int l = 1, cnt = 0;
	for (int r = 1; r <= n; r++) {
		while (l <= r && arr[r] - arr[l] > d)
			l++;

		if (r - l >= 2) {
			int c = r - l;
			cnt += (c * (c - 1)) / 2;
		}																														
	}
	cout << cnt << endl;
}

int32_t main() {
	solve();
	return 0;
	int n, d;
	cin >> n >> d;

	// arr[1, n] is strictly increasing
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	int r = 1;
	int cnt = 0;
	for (int l = 1; l <= n; l++) {
		while (r <= n && arr[r] - arr[l] <= d)
			r++;
		// [l, r - 1]
		if (r >= 2 && r - l >= 3) {
			// [l + 1, r - 1]
			int c = r - l - 1;
			cnt += (c * (c - 1)) / 2;
		}
	}

	cout << cnt << endl;
	return 0;
}