#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int w, b;
	cin >> w >> b;

	int left = 0;
	int right = w + b + 1;

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if ((mid * (mid + 1)) / 2 <= w + b)
			left = mid;
		else
			right = mid;
	}

	cout << left << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}