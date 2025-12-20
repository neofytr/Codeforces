#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	if (n == 9 || n == 10 || n == 11) {
		cout << "7 3 3 7 5 3 7 7 3" << endl;
		return;
	}

	int i = 1;
	int k = n / 6;
	for (int r = 1; r <= k; r++) {
		for (int j = 1; j <= 3; j++)
			cout << i << " " << i + 1 << " ";
		i += 2;
	}

	if (8 * k > n) {
		for (int r = 1; r <= n % 6; r++)
			cout << i++ << " ";
	} else {
		int rem = n % 6;
		int pairs = rem / 2;
		int left = rem & 1;

		for (int r = 1; r <= pairs; r++)
			cout << i << " " << i + 1 << " ";
		if (left)
			cout << i << " ";
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