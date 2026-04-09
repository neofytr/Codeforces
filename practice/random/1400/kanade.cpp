#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k;
	cin >> n >> k;

	set<int> s;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r], s.insert(arr[r]);

	sort(arr.begin() + 1, arr.end());
	for (int r = 1; r <= n; r++) {
		if (s.find(arr[r]) == s.end())
			continue;

		if (k / arr[r] > n) {
			cout << -1 << endl;
			return;
		}

		for (int x = 2; x <= k / arr[r]; x++) {
			if (s.find(x * arr[r]) == s.end()) {
				cout << -1 << endl;
				return;
			}
		}
	}

	for (int r = 1; r <= n; r++) {
		if (s.find(arr[r]) == s.end())
			continue;

		for (int x = 2; x <= k / arr[r]; x++) 
			s.erase(x * arr[r]);
	}

	cout << s.size() << endl;
	for (int e : s)
		cout << e << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}