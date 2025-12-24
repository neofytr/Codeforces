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

					if (!(b[r] % one) && (r == 1 || (r >= 2 && !(one % b[r - 1]))))
						f[b[r] / one]++;
					if (one != two && !(b[r] % two) && (r == 1 || (r >= 2 && !(two % b[r - 1]))))
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

	for (int r = 1; r <= n - 1; r++)
		if (b[r + 1] % b[r])
			cout << b[r] / x << " ";
		else cout << b[r] << " ";
	cout << b[n] << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}