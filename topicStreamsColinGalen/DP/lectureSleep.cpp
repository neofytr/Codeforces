#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAXN 1e5

int32_t main() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1), t(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> t[r];

	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + a[r];

	vector<vector<int>> dp(n + 1, vector<int>(2, LLONG_MIN));
}