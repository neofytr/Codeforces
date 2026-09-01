#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int t) {
	int n, x; cin >> n >> x;
	vector<int> arr(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	sort(arr.begin() + 1, arr.end());
	int p = 0, res = 0;
	for (int i = 1; i <= n; i++) {
		p += arr[i];
		int alp = ((double)(x - p) / i) + 1.0;
		if (alp >= 1) res += alp;
	}

	cout << res << endl;
}

int32_t main() {
	int t; cin >> t;
	for (int i = 1; i <= t; i++) solve(i);
	return 0;
}