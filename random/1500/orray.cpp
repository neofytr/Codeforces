#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	int maxi = LLONG_MIN;
	int p = 0;
	vector<multiset<int>> b(31);
	vector<int> a(n + 1), f(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i], maxi = max(a[i], maxi);

	bool done = false;
	for (int i = 1; i <= n; i++)
		if (a[i] == maxi && !done) {
			done = true;
			continue;
		} else 
			for (int bit = 0; bit <= 30; bit++)
				if (a[i] & (1ll << bit))
					b[bit].insert(a[i]);

	f[1] = maxi, p = f[1];
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

		if (val == -1)
			for (int bit = 30; bit >= 0; bit--)
				if (!b[bit].empty()) {
					val = *b[bit].rbegin();
					break;
				}

		f[i] = val, p |= f[i];
		for (int bit = 30; bit >= 0; bit--)
			if (b[bit].find(val) != b[bit].end())
				b[bit].erase(b[bit].find(val));
	}

	vector<int> k = {0, 12,  3, 10, 4, 9, 9};
	p = 0;
	for (int i = 1; i <= n; i++)
		cout << (p |= f[i]) << " ";

	cout << endl;
	p = 0;
	for (int i = 1; i <= n; i++)
		cout << (p |= k[i]) << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}