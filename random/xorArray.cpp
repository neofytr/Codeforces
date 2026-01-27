#include <bits/stdc++.h>
using namespace std;

#define int long long

int calc(int l, int r, vector<int> &a) {
	int res = 0;
	for (int i = l; i <= r; i++)
		res ^= a[i];
	return res;
}

void solve() {
	int n, l, r;
	cin >> n >> l >> r;

	vector<int> a(n + 1);

	int x = 0, c = 3, cons = 0;
	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (i == r) {
		 	a[i] = res, c = res + 1, cons = 1;
		 	continue;
		}

		if (cons == 3) a[i] = c + 1, c += 2, cons = 1;
		else a[i] = c++, cons++;
		
		if (i >= l && i < r) res ^= a[i];
	}

	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";

	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			cout << i << " " << j << " " << calc(i, j, a) << endl; 
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}