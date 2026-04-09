#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(2 * 1e5)

int A[MAX + 1], B[MAX + 1];
void solve() {
	int a, b, k;
	cin >> a >> b >> k;

	int v;
	vector<pair<int, int>> p(k + 1);
	for (int r = 1; r <= max(a, b); r++)
		A[r] = B[r] = 0;

	for (int r = 1; r <= k; r++)
		cin >> v, A[v]++, p[r].first = v;
	for (int r = 1; r <= k; r++)
		cin >> v, B[v]++, p[r].second = v;

	int res = 0;
	for (int r = 1; r <= k; r++) {
		int b = p[r].first, g = p[r].second;
		res += (k - (A[b] - 1) - (B[g] - 1) - 1);
	}

	cout << res / 2 << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}