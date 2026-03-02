#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, s; cin >> n >> s;
	vector<int> d(25, 0);

	int x = n;

	int i = 0;
	while (x) 
		d[i++] = x % 10, x /= 10;

	int sum = 0;
	for (int r = 0; r < i; r++)	sum += d[r];
	if (sum <= s) {
		cout << 0 << endl;
		return;
	}

	for (int r = 0; r < i; r++) {
		sum -= d[r], sum += 1, d[r + 1]++, d[r] = 0;
		if (sum <= s) break;
	}

	for (int r = 0; r <= i; r++)
		if (r >= 10)
			d[r + 1] += d[r] / 10, d[r] = d[r] % 10;

	x = 0;
	int p = 1;
	for (int r = 0; r <= i + 1; r++)
		x += p * d[r], p *= 10;
	cout << x - n << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}