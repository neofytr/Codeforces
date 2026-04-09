#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	string s; cin >> s;
	vector<int> str(n + 1);
	for (int r = 1; r <= n; r++) str[r] = (s[r - 1] == '+' ? 1 : 0);

	int a = 0, b = 0;
	for (int r = 1; r <= n; r++)
		if (str[r]) a++;
		else b++;

	int q; cin >> q;
	while (q--) {
		int x, y; cin >> x >> y;
		if (x == y) {
			if (a == b) cout << "YES" << endl;
			else cout << "NO" << endl;
			continue;
		}

		if (llabs(y * (b - a)) % llabs(x - y)) {
			cout << "NO" << endl;
			continue;
		}

		int z = (y * (a - b)) / (x - y);
		if (z > b || z + a < 0) {
			cout << "NO" << endl;
			continue;
		}

		cout << "YES" << endl;
	}
	return 0;
}