#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++)
		p[r] = p[r - 1] ^ a[r];

	vector<int> next(n + 1, -1);

	int i = 1, j = 1;
	while (i <= n) {
		j = i;
		if (a[i] == b[i]) {
			i++;
			continue;
		}

		int g = 0;
		while (j <= n && ((g ^ a[j]) != b[i]))
			g ^= a[j],  j++;

		if (j <= n)
			g ^= a[j], next[i] = j;
		else if (j > n) {
			cout << "NO\n";
			return;
		}

		i = j;
	}

	i = 1;
	while (i <= n) {
		if (next[i] == -1) {
			i++;
			continue;
		}
		for (int j = i; j < next[i]; j++)
			if ((p[next[i]] ^ p[j - 1]) != b[j]) {
				cout << "NO\n";
				return;
			}
		i = next[i];
	}

	cout << "YES" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}