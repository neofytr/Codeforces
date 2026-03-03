#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	string s; cin >> s;

	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = s[i - 1] - 'a';

	int maxi = LLONG_MIN;
	for (int i = 1; i <= n; i++) maxi = max(str[i], maxi);

	if (maxi <= k) {
		string res;
		for (int i = 1; i <= n; i++) res.push_back('a');
		cout << res << endl;
		return;
	}

	vector<int> conv(26, 0);
	for (int i = 0; i < 26; i++) conv[i] = i;

	for (int i = 1; i <= n; i++) {
		int x = str[i];
		if (!x) continue;

		if (conv[x] != x) {
			while (conv[x] != x)
				x = conv[x];

			str[i] = x;
			continue;
		}

		int curr = x;
		while (k && curr && conv[curr] == curr) {
			curr--, k--;
			conv[curr + 1] = curr;
		}

		while (conv[curr] != curr)
			curr = conv[curr];
		str[i] = curr;
	}

	string res;
	for (int i = 1; i <= n; i++) res.push_back(str[i] + 'a');
	cout << res << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}