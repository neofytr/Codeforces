#include <bits/stdc++.h>
using namespace std;

#define int uint64_t

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];	

	if (k == 1) {
		for (int r = 1; r <= n; r++)
			if (arr[r] & 1)
				cout << arr[r] + 1 << " ";
			else 
				cout << arr[r] << " ";
	} else if (k == 2) {
		for (int r = 1; r <= n; r++)
			if (arr[r] % 3 == 1)
				cout << arr[r] + 2 << " ";
			else if (arr[r] % 3 == 2)
				cout << arr[r] + 4 << " ";
			else 
				cout << arr[r] << " ";
	} else {
		for (int r = 1; r <= n; r++)
			cout << arr[r] + (k - 1 - arr[r] % (k - 1)) * k << " ";
	}
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}