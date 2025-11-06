#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	set<int> s;
	for (int r = 1; r <= n; r++)
		cin >> arr[r], s.insert(arr[r]);

	bool allEqual = true;
	int c = arr[1];
	for (int r = 1; r <= n; r++)
		if (arr[r] != c) {
			allEqual = false;
			break;
		}
	if (allEqual) {
		cout << "YES\n";
		return;
	}

	bool one = false, zero = false;
	for (int r = 1; r <= n; r++) {
		if (!arr[r]) zero = true;
		if (arr[r] == 1) one = true;
	}

	if (!zero && !one) {
		cout << "YES\n";
		return;
	}

	if (zero && one) {
		cout << "NO\n";
		return;
	}

	if (zero) {
		cout << "YES\n";
		return;
	}

	for (int r = 1; r <= n; r++)
		if (s.count(arr[r] - 1)) {
			cout << "NO\n";
			return;
		}

	cout << "YES\n";
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}