#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, k; cin >> n >> k;

	int left = 0;
	int right = (int)(2 * 1e9);

	auto can = [&n, &k](int v) {
		int j = 1;
		int sum = 0;
		while (v / j)
			sum += v / j, j *= k;
		return sum >= n;
	};

	while (right != left + 1) {
		int mid = left + ((right - left) >> 1);
		if (can(mid)) right = mid;
		else left = mid;
	}
	cout << right << endl;
	return 0;
}