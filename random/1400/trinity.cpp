#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int t) {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	sort(arr.begin() + 1, arr.end());
}

int32_t main() {
	int t; cin >> t;
	for (int r = 1; r <= t; r++) solve(r);
	return 0;
}