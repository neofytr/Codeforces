#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	string str;
	cin >> str;

	vector<int> v(n + 1);
	for (int r = 1; r <= n; r++) v[r] = str[r - 1] - '0';

	vector<int> p(n + 1);
	for (int r = 1; r <= n; r++) p[r] = r;

	int l = 1, r = 1;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}