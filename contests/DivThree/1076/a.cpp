#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, s, x;
	cin >> n >> s >> x;

	int sum = 0, v;
	for (int r = 1; r <= n; r++)
		cin >> v, sum += v;

	if (s < sum) {
		cout << "NO" << endl;
		return;
	}

	if (!((s - sum) % x))
		cout << "YES" << endl;
	else 
		cout << "NO" << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}