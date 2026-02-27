#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	unordered_map<pair<int, int>, int> f;
	int c = 0;
	for (int r = 1; r <= n; r++)
		if (!a[r] && !b[r]) c++;
		else if (a[r]) {
			int g = gcd(b[r], a[r]);
			f[{-1 * (b[r] / g), a[r] / g}]++;
		}

	int maxi = LLONG_MIN;
	for (auto &[_, cnt] : f) maxi = max(maxi, cnt);
	
	return 0;
}