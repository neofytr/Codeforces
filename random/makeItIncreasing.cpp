#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	int ops = 0;
	for (int r = n - 1; r >= 1; r--) {
		if (!arr[r + 1]) {
			cout << -1 << endl;
			return;
		}
		while(arr[r] >= arr[r + 1])
			ops++, arr[r] /= 2;
	}
		

	for (int r = 2; r <= n; r++)
		if (arr[r] == arr[r - 1]) {
			cout << -1 << endl;
			return;
		}
	cout << ops << endl;
	return;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}