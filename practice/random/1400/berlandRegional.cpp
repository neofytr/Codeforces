#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	int v;
	vector<vector<int>> u(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> v, u[v].push_back(r);

	vector<int> s(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> s[r];

	vector<int> res(n + 1, 0);
	for (int r = 1; r <= n; r++) {
		auto &vec = u[r];
		int sz = vec.size();

		for (int i = 0; i < sz; i++)
			vec[i] = s[vec[i]];

		sort(vec.begin(), vec.end(), greater<int>());

		vector<int> p(sz + 1, 0);
		p[0] = 0;
		for (int r = 1; r <= sz; r++)
			p[r] += p[r - 1] + vec[r - 1];

		for (int r = 1; r <= sz; r++) {
			int end = (sz - 1) - sz % r;
			res[r] += p[end + 1];
		}
	}

	for (int r = 1; r <= n; r++)
		cout << res[r] << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}