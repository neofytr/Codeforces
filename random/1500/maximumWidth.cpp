#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m; cin >> n >> m;
	string r1, r2; cin >> r1 >> r2;

	vector<int> s(n + 1), t(m + 1);
	for (int i = 1; i <= n; i++) s[i] = r1[i - 1] - 'a';
	for (int i = 1; i <= m; i++) t[i] = r2[i - 1] - 'a';

	vector<vector<int>> f(26);
	for (int i = 1; i <= n; i++) f[s[i]].push_back(i);

	vector<int> maxi(m + 1);
	maxi[m] = *f[t[m]].rbegin();
	for (int i = m - 1; i >= 1; i--) {
		auto itr = lower_bound(f[t[i]].begin(), f[t[i]].end(), maxi[i + 1]);
		maxi[i] = *(--itr);
	}

	vector<int> mini(m + 1);
	mini[1] = *f[t[1]].begin();
	for (int i = 2; i <= m; i++) {
		auto itr = lower_bound(f[t[i]].begin(), f[t[i]].end(), mini[i - 1]);
		mini[i] = *itr;
	}

	int res = LLONG_MIN;
	for (int i = 1; i <= m - 1; i++) res = max(res, maxi[i + 1] - mini[i]);
	cout << res << endl;
	return 0;
}