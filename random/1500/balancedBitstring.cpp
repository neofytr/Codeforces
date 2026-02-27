#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	string s; cin >> s;

	vector<int> str(n + 1), ones(n + 2, 0), zeroes(n + 2, 0);
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
			} else if (o == k / 2) {
				zeroes[l] += 1;
				zeroes[r + 1] -= 1;
			} else if (z == k / 2) {
				ones[l] += 1;
				ones[r + 1] -= 1;
			}
	}

	for (int r = 1; r <= n; r++) {
		ones[r] += ones[r - 1];
		zeroes[r] += zeroes[r - 1];

		if (str[r] == 2 && ones[r] && zeroes[r]) {
			cout << "NO" << endl;
			return;
		}
	}

	for (int r = 1; r <= n; r++) 
		if (str[r] == 2) {
			if (ones[r]) str[r] = 1;
			else if (zeroes[r]) str[r] = 0;
		}
	
	
	o = z = 0;
	l = 1;
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

	cout << "YES" << endl;
	return;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}