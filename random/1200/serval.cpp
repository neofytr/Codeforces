#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1), zeroes;
	for (int r = 1; r <= n; r++) {
		cin >> arr[r];
		if (!arr[r]) zeroes.push_back(r);
	}

	if (zeroes.empty()) {
		cout << 1 << endl;
		cout << 1 << " " << n << endl;
	} else if (zeroes.size() >= 2) {
		if (!arr[1] && !arr[2] && zeroes.size() == 2) {
			cout << 2 << endl;
			cout << 1 << " " << 2 << endl;
			cout << 1 << " " << n - 1 << endl;
			return;
		}

		if (!arr[n - 1] && !arr[n] && zeroes.size() == 2) {
			cout << 2 << endl;
			cout << n - 1 << " " << n << endl;
			cout << 1 << " " << n - 1 << endl;
			return;
		}

		cout << 3 << endl;
		if (zeroes[0] == 1) {
			cout << 1 << " " << 2 << endl;
			cout << 2 << " " << n - 1 << endl;
			cout << 1 << " " << 2 << endl;
		} else {
			cout << 1 << " " << zeroes[0] << endl;
			int rem = zeroes[0] - 1;
			cout << 2 << " " << n - rem << endl;
			cout << 1 << " " << 2 << endl;
		}
	} else {
		cout << 2 << endl;
		if (zeroes[0] != n) {
			cout << zeroes[0] << " " << zeroes[0] + 1 << endl;
			cout << 1 << " " << n - 1 << endl;
		} else {
			cout << zeroes[0] - 1 << " " << zeroes[0] << endl;
			cout << 1 << " " << n - 1 << endl;
 		}
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
}