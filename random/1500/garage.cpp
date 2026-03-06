#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;

	if (n == 1) {
		cout << 3 << endl;
		return 0;
	}

	int left = 3;
	int right = 1e12;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;

		int cnt = 0;
		if (mid >= 5) cnt += ((mid - 5) / 4 + 1);
		if (mid >= 3) cnt += ((mid - 3) / 4 + 1);
		if (mid >= 8) cnt += ((mid - 8) / 4 + 1);
		if (cnt < n) left = mid;
		else right = mid;

	}

	cout << right << endl;
	return 0;
}