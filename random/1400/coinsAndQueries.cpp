#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, q; cin >> n >> q;
	vector<int> d(63 + 1, 0);

	int v;
	for (int r = 1; r <= n; r++) {
		cin >> v;
		for (int b = 0; b <= 63; b++)
			if (v & (1ll << b)) {
				d[b]++;
				break;
			}
	}

	while (q--) {
		cin >> v;
		int cnt = 0;
		int left = 0;
		for (int b = 63; b >= 0; b--) {
			if (v & (1ll << b)) left += (1ll << b);
			if (d[b]) {
				int req = left >> b;
				int j = min(d[b], req);
				cnt += j;
				left -= j * (1ll << b);
			}
		}
		if (left) cout << -1 << endl;
		else cout << cnt << endl;
	}
	return 0;
}