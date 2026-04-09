#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	int s = -1;
	for (int b = 29; b >= 0; b--)
		if (n & (1ll << b)) {
			s = b;
			break;
		}

	if (s == -1) {
		cout << "YES\n";
		return;
	}

	for (int start = 63; start >= s; start--) {
		int num = start + 1;
		if (num & 1) {
			bool can = true;
			for (int b = 0; b <= num / 2 - 1; b++) {
				bool first = (1ll << (start - b)) & n;
				bool last = (1ll << b) & n;

				if (first != last) {
					can = false;
					break;
				}
			}

			bool mid = (1ll << (num / 2)) & n;
			if (mid)
				can = false;

			if (can) {
				cout << "YES\n";
				return;
			}
		} else {
			bool can = true;
			for (int b = 0; b <= num / 2; b++) {
				bool first = (1ll << (start - b)) & n;
				bool last = (1ll << b) & n;

				if (first != last) {
					can = false;
					break;
				}
			}

			if (can) {
				cout << "YES\n";
				return;
			}
		}
	}

	cout << "NO\n";
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}