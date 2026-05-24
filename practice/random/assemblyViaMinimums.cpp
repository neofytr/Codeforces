#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	int b; 	map<int, int> f;
	int maxi = LLONG_MIN;
	for (int i = 1; i <= (n * (n - 1)) / 2; i++) cin >> b, f[-1 * b]++, maxi = max(maxi, b);

	vector<int> ans = {maxi};
	for (auto &[elt, cnt] : f) {
		int c = 0;
		int curr = ans.size();
		for (int i = curr; i <= n + curr; i++) {
			c += i; ans.push_back(-1 * elt);
			if (c == cnt) break;
		}
	}

	for (int e : ans)
		cout << e << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}