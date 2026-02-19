#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> A(n + 1), B(n + 1);
	for (int r = 1; r <= n; r++) cin >> A[r];
	for (int r = 1; r <= n; r++) cin >> B[r];

	auto can = [&A, &B, &n](int x) -> bool {
		// can we make the movie rating atleast x?
		// min(rating A, rating B) >= x
		// thus, rating A, rating B >= x
		int a = 0, b = 0;
		for (int r = 1; r <= n; r++)
			if (A[r] == 1 && B[r] != 1) a += 1;
			else if (B[r] == 1 && A[r] != 1) b += 1;
			else if (A[r] == 1 && B[r] == 1) {
				if (a >= b) b += 1;
				else a += 1;
			}
		return a >= x && b >= x;
	};

	int left = -1 * n - 1;	
	int right = n + 1;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid)) left = mid;
		else right = mid;
	}

	cout << left << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}