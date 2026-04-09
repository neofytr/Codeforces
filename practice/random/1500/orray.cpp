#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	int maxi = LLONG_MIN;
	int p = 0;
	vector<vector<int>> b(31);
	unordered_map<int, int> was, done;
	vector<int> a(n + 1), f(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i], maxi = max(a[i], maxi), was[a[i]]++;

	bool cause = false;
	for (int i = 1; i <= n; i++)
		if (a[i] == maxi && !cause) {
			cause = true;
			continue;
		} else 
			for (int bit = 0; bit <= 30; bit++)
				if (a[i] & (1ll << bit))
					b[bit].push_back(a[i]);

	f[1] = maxi, p = f[1];
	done[f[1]]++;
	for (int i = 2; i <= n; i++) {
		int val = -1;
		int x = 0;
		for (int bit = 30; bit >= 0; bit--)
			if (!(p & (1ll << bit)))
				x |= (1ll << bit);

		for (int bit = 30; bit >= 0; bit--)
			if (!(p & (1ll << bit)) && !b[bit].empty()) {
				int elt = -1, k = LLONG_MIN;
				for (int c : b[bit])
					if ((x & c) > k) elt = c, k = x & c;

				val = elt;
				break;
			}

		if (val == -1) {
			int idx = i;
			for (int bit = 30; bit >= 0; bit--)
				if (!b[bit].empty()) {
					for (int c : b[bit])
						if (done[c] < was[c])
							done[c]++, f[idx++] = c;
				}
			break;
		}

		f[i] = val, p |= f[i], done[f[i]]++;
	}

	for (int i = 1; i <= n; i++)
		cout << f[i] << " ";
	cout << endl;
}

int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t; cin >> t;
	while (t--) solve();
	return 0;
}