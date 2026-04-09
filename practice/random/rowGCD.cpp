#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> a[r];

	int g = 0;
	for (int r = 2; r <= n; r++)
		g = gcd(g, abs(a[r] - a[1]));

	vector<int> b(m + 1);
	for (int r = 1; r <= m; r++)
		cin >> b[r];

	for (int r = 1; r <= m; r++) {
		cout << gcd(a[1] + b[r], g) << " ";
	}
	cout << endl;
	return 0;
}