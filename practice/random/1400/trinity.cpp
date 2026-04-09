#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int t) {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	int mini = LLONG_MAX;
	sort(arr.begin() + 1, arr.end());
	for (int r = 1; r <= n - 1; r++) {
		auto itr = lower_bound(arr.begin() + 1, arr.end(), arr[r] + arr[r + 1]);
		auto i = itr - arr.begin();
		mini = min(mini, n + r - i);
	}

	cout << mini << endl;
}

int32_t main() {
	int t; cin >> t;
	for (int r = 1; r <= t; r++) solve(r);
	return 0;
}