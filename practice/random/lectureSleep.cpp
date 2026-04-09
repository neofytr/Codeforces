#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1), t(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> a[r];
	for (int r = 1; r <= n; r++)
		cin >> t[r];

	int l = 1;
	int sum = 0;

	int maxi = LLONG_MIN;

	for (int r = 1; r <= n; r++) {
		if (!t[r])
			sum += a[r];

		if (r - l + 1 == k) {
			maxi = max(maxi, sum);
			if (!t[l])
				sum -= a[l];
			l++;
		}
	}
	for (int r = 1; r <= n; r++)
		if (t[r])
			maxi += a[r];
	cout << maxi << endl;
	return 0;
}