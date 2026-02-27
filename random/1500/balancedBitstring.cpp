#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	string s; cin >> s;

	vector<int> str(n + 1);
	for (int r = 1; r <= n; r++)  
		if (s[r - 1] == '0') str[r] = 0;
		else if (s[r - 1] == '1') str[r] = 1;
		else str[r] = 2;

	int o = 0, z = 0;
	int l = 1;
	for (int r = 1; r <= n; r++) {
		if (!str[r]) z++;
		else if (str[r] == 1) o++;

		while (r - l + 1 > k) {
			if (!str[l]) z--;
			else if (str[l] == 1) o--;
			l++;
		}

		if (r - l + 1 == k) 
			if (o > k / 2 || z > k / 2) {
				cout << "NO" << endl;
				return;
			}
	}

	o = 0, z = 0;
	for (int r = 1; r <= k; r++)
		if (!str[r]) z++;
		else if (str[r] == 1) o++;

	int l = 1;
	for (int r = k + 1; r <= n; r++) {
		int no = o, nz = z;
		if (!str[r]) nz++;
		else if (str[r] == 1) no++;

		if (!str[l]) nz--;
		else if (str[l] == 1) no--;
		l++;

		if (str[l - 1] != 2 && str[r] != 2) {
			if (o != no || z != nz) {
				cout << "NO" << endl;
				return;
			}
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}