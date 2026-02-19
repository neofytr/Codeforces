#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	vector<int> v(n + 1);
	for (int r = 1; r <= n; r++) v[r] = (s[r - 1] - '0');

	int mini = LLONG_MAX;
	for (int k = 1; k <= n - 1; k++) {
		int res = v[k] * 10 + v[k + 1];
		int sum = 0;
		for (int r = 1; r <= n; r++)
			if (r == k) r++;
			else if (!v[r]) {
				cout << 0 << endl;
				return;
			} else if (v[r] == 1) continue;
			else sum += v[r];

		if (!sum) sum = res;
		else if (res == 1) sum *= res;
		else sum += res;
		mini = min(mini, sum);
	}
	cout << mini << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}