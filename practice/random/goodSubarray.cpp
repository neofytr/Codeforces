#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n; string str;
	cin >> n >> str;

	vector<int> arr(n + 1), p(n + 1, 0);
	for (int r = 1; r <= n; r++) arr[r] = str[r - 1] - '0', p[r] = p[r - 1] + arr[r];

	// arr[l, r] is good, for some 1 <= l <= r <= n, iff 
	// sum[l, r] = r - l + 1
	// iff p[r] - p[l - 1] = r - l + 1
	// iff p[r] - r = p[l - 1] - (l - 1) 

	// For any 1 <= r <= n, arr[l, r] is good iff p[r] - r = p[l] - l
	// for 0 <= l <= r - 1

	int cnt = 0;
	unordered_map<int, int> f;
	f[p[0] - 0]++;
	for (int r = 1; r <= n; r++) {
		int target = p[r] - r;
		cnt += f[target];
		f[target]++;
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}