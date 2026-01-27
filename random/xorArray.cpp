#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, l, r;
	cin >> n >> l >> r;

	vector<int> a(n + 1);
	vector<int> p(n + 1);

	p[0] = 0;
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		if (i == r) p[i] = p[l - 1];
	}

	for (int i = 1; i <= n; i++)
		a[i] = p[i] ^ p[i - 1], cout << a[i] << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}