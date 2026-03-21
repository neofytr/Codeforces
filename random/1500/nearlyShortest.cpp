#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = s[i] - 'a';

	vector<vector<int>> p(n + 1, vector<int>(26, 0));
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 26; j++)
			p[i][j] = p[i - 1][j] + (str[i] == j);

	auto check = [&](int x) -> bool {
		int div = n / x;
		int diff = 0;
		for (int j = 0; j < 26; j++)
			diff += llabs(p[x][j] * div - p[n][j]);
		return diff <= 2;
	};

	vector<bool> done(n + 1, false);
	for (int i = 1; i * i <= n; i++)
		if (!(n % i)) {
			done[i] = check(i), done[n / i] = check(n / i);
		}

	for (int i = 1; i <= n; i++)
		if (done[i]) {
			cout << i << endl;
			return;
		}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}