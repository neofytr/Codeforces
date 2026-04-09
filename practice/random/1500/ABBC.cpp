#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	string s; cin >> s;
	int n = s.length();
	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = s[i - 1] - 'A';

	if (n == 1) {
		cout << 0 << endl;
		return;
	}

	int cntB = 0;
	for (int i = 1; i <= n; i++) cntB += str[i];
	vector<int> lens;
	int res = 0;

	int i = 1, j = 1;
	while (i <= n) {
		while (i <= n && str[i]) i++;
		j = i;
		while (j <= n && !str[j]) j++;
		lens.push_back(j - i);
		i = j;
	}

	sort(lens.begin(), lens.end());
	reverse(lens.begin(), lens.end());
	for (int i = 0; i < min((int)lens.size(), cntB); i++)
		res += lens[i];
	cout << res << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}