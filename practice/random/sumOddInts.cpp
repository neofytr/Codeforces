#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k;
	cin >> n >> k;

	// n >= 1
	// find if n can be represented as a sum of k distinct positive odd integers

	if ((n - k) & 1) {
		cout << "NO\n";
		return;
	}

	int w = (n - k) / 2;
	if (w >= (k * (k - 1)) / 2)
		cout << "YES\n";
	else 
		cout << "NO\n";
	return;
}

int32_t main() {
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
}