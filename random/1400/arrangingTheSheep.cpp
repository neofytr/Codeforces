#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	string str;
	cin >> str;

	int cnt = 0;
	vector<int> vec(n + 1);
	for (int r = 1; r <= n; r++)
		vec[r] = (str[r - 1] == '*' ? (cnt++, 1) : 0);

	int i = 1;
	vector<int> g(cnt + 1);
	for (int r = 1; r <= n; r++)
		if (vec[r]) g[i++] = n - cnt + k - r;

	cout << mini << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}