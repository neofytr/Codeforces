#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1);
	vector<int> p(n + 1);

	for (int r = k; r >= 1; r--)
		cin >> p[n - r + 1];

	for (int r = n - k + 2; r <= n; r++)
		a[r] = p[r] - p[r - 1];
	
	bool can = true;
	for (int r = n - k + 3; r <= n; r++)
		if (a[r] < a[r - 1]) {
			can = false;
			break;
		} 

	if (k >= 2)
		if (p[n - k + 1] > (n - k + 1) * a[n - k + 2])
			can = false;

	cout << (can ? "YES" : "NO") << endl;
}

int32_t main() {
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}