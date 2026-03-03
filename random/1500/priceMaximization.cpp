#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	int sum = 0;
	vector<int> rem(k + 1, 0);
	for (int i = 1; i <= n; i++) {
		sum += a[i] / k;
		rem[a[i] % k]++;
	}

	int l = 1, r = k - 1;
	while (l < r) {
		if (!rem[l]) l++;
		if (!rem[r]) r--;
		if (l < r && l + r >= k) {
			sum += min(rem[l], rem[r]);
			if (rem[l] < rem[r]) rem[r] -= rem[l], rem[l] = 0, l++;
			else if (rem[r] < rem[l]) rem[l] -= rem[r], rem[r] = 0, r--;
			else rem[r] = 0, rem[l] = 0, l++, r--;
		} else l++;
	}

	for (int i = 1; i <= k - 1; i++)
		if (2 * i >= k) sum += (rem[i] / 2);

	cout << sum << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}