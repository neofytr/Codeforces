#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, x;
	cin >> n >> x;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	vector<int> f(n + 1);
	unordered_map<int, int> extra;

	for (int r = 1; r <= n; r++)
		if (arr[r] <= n) f[arr[r]]++;

	for (int r = 0; r < n; r++)
		if (f[r]) extra[r % x] += f[r] - 1;
		else {
			int rem = r % x;
			if (!extra[rem]) {
				cout << r << endl;
				return;
			}
			extra[rem]--;
		}

	cout << n << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}