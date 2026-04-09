#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX 1e5

int f(int x) {
	if (x == 1 || x == 2)
		return 1;
	return (1ll << (x - 2));
}

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	int m = arr[1];
	for (int r = 2; r <= n; r++) {
		int a = arr[r] - m;
		if (a >= m) {
			cout << "NO\n";
			return;
		}
		m = min(m, arr[r]);
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