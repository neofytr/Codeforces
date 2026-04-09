#include <bits/stdc++.h>
using namespace std;

#define int long long

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1, 0);
	vector<int> alt1(1), alt2(1), alt3(1);
	bool used = false;
	for (int r = 1; r <= n; r++) cin >> a[r];

	alt1.push_back(a[1]), alt2.push_back(a[1]), alt3.push_back(a[1]);
	for (int r = 1; r <= n - 1; r++) {
		b[r] = gcd(a[r], a[r + 1]);
		if (b[r] < b[r - 1]) {
			// dont take a[r + 1]
			for (int i = r + 2; i <= n; i++) alt2.push_back(a[i]);

			// dont take a[r]
			alt1.pop_back();
			for (int i = r + 1; i <= n; i++) alt1.push_back(a[i]);

			if (r >= 2) {
				// dont take a[r - 1]
				alt3.pop_back(), alt3.pop_back();
				used = true;
				for (int i = r; i <= n; i++) alt3.push_back(a[i]);
			}
			break;
		} else alt1.push_back(a[r + 1]), alt2.push_back(a[r + 1]), alt3.push_back(a[r + 1]);
	}

	int sz = alt1.size() - 1;
	bool can = true;
	for (int r = 1; r <= sz - 1; r++) {
		b[r] = gcd(alt1[r], alt1[r + 1]);
		if (b[r] < b[r - 1]) {
			can = false;
			break;
		}
	}

	if (can) {
		cout << "YES" << endl;
		return;
	}

	sz = alt2.size() - 1;
	can = true;
	for (int r = 1; r <= sz - 1; r++) {
		b[r] = gcd(alt2[r], alt2[r + 1]);
		if (b[r] < b[r - 1]) {
			can = false;
			break;
		}
	}

	if (can) {
		cout << "YES" << endl;
		return;
	}

	if (!used) {
		cout << "NO" << endl;
		return;
	}

	sz = alt3.size() - 1;
	for (int r = 1; r <= sz - 1; r++) {
		b[r] = gcd(alt3[r], alt3[r + 1]);
		if (b[r] < b[r - 1]) {
			cout << "NO" << endl;
			return;
		}
	}

	cout << "YES" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}