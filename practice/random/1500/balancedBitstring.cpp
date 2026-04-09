#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	string s; cin >> s;

	vector<int> a(n + 1), ones(n + 2, 0), zeroes(n + 2, 0);
	for (int r = 1; r <= n; r++)  
		if (s[r - 1] == '0') a[r] = 0;
		else if (s[r - 1] == '1') a[r] = 1;
		else a[r] = 2;

	int fz = 0, fo = 0;
	for (int r = 1; r <= k; r++) {
		bool z = false, o = false;
		for (int i = r; i <= n; i += k)
			if (!a[i] && o) {
				cout << "NO" << endl;
				return;
			} else if (a[i] == 1 && z) {
				cout << "NO" << endl;
				return;
			} else if (a[i] == 1 && !o) o = true;
			else if (!a[i] && !z) z = true;

		if (z) fz++;
		if (o) fo++;
	}

	if (fz > k / 2 || fo > k / 2) 
		cout << "NO" << endl;
	else cout << "YES" << endl;
	return;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}