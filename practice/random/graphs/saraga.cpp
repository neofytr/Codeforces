#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s, t;
	cin >> s >> t;

	int n = s.size(), m = t.size();
	vector<int> S(n + 1), T(m + 1);
	for (int r = 1; r <= n; r++)
		S[r] = s[r - 1] - 'a';
	for (int r = 1; r <= m; r++)
		T[r] = t[r - 1] - 'a';

	if (m == 1 || n == 1) {
		cout << -1 << endl;
		return 0;
	}

	vector<int> f(26, LLONG_MIN);
	for (int r = 1; r <= m - 1; r++)
		f[T[r]] = r;

	int mini = LLONG_MAX;
	int p;
	for (int r = 1; r <= n - 1; r++) {
		int nxt = S[r + 1];
		if (f[nxt] == LLONG_MIN) continue;
		if (r + 1 + (m - (f[nxt] + 1) + 1) < mini)
			mini = r + 1 + (m - (f[nxt] + 1) + 1), p = r;
	}
	if (mini == LLONG_MAX) {
		cout << -1 << endl;
		return 0;
	}

	string res;
	for (int r = 1; r <= p + 1; r++)
		res.push_back(char(S[r] + 'a'));
	for (int r = f[S[p + 1]] + 1; r <= m; r++)
		res.push_back(char(T[r] + 'a'));
	cout << res << endl;
	return 0;
}