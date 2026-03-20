#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> a(n);
	for (auto &x : a) cin >> x;

	sort(a.begin(), a.end());

	// check function
	auto ok = [&](int k) {
		for (int i = 0; i < k; i++) {
			if (a[i] >= a[i + k + 1]) return false;
		}
		return true;
	};

	// binary search k
	int l = 0, r = n, ans = 0;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (mid <= (n - 1) / 2 && ok(mid)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}

	cout << ans << endl;

	vector<int> res;

	int i = 0, j = ans;

	// interleave
	while (i < ans && j < n) {
		res.push_back(a[j++]); // big
		res.push_back(a[i++]); // small
	}

	while (j < n) res.push_back(a[j++]);

	for (auto x : res) cout << x << " ";
	cout << endl;

	return 0;
}