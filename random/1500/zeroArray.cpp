#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];

	sort(a.begin() + 1, a.end());

	int l = 1, r = n;
	while (l < r) {
		int sum = 0;
		while (l < r && sum + a[l] <= a[r])
			sum += a[l++];

		if (l == r) {
			if (sum == a[r]) cout << "YES" << endl;
			else cout << "NO" << endl;
			return;
		}

		if (sum == a[r])
			l++, r--;
	}
	return 0;
}