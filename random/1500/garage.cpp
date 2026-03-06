#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;

	if (n == 1) {
		cout << 3 << endl;
		return 0;
	}

	auto cnt = [](int x) {
		if (x < 3) return 0;

		int res = 0;
		for (int b = 1; (x - b * b) / (2 * b) >= 1; b++)
			res += (x - b * b) / (2 * b);
		return res;
	};	

	int left = 3;
	int right = 1e12;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
	}

	cout << right << endl;
	return 0;
}