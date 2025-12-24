#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r];

	unordered_map<int, int> f;
	int cnt = 0;
	for (int r = 1; r <= n - 1; r++) {
		if (b[r + 1] % b[r]) {
			cnt++;
			for (int i = 1; i * i <= b[r + 1]; i++)
				if (!(b[r + 1] % i)) {
					int one = i;
					int two = b[r + 1] / i;

					if (!(b[r] % one))
						f[b[r] / one]++;
					if (one != two && !(b[r] % two))
						f[b[r] / two]++;
				}
		}
	}

	int x;
	if (!cnt) {
		x = 1;
	}

	for (auto &[e, c] : f) {
		if (c == cnt) {
			x = e;
			break;
		}
	}

	cout << x << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}