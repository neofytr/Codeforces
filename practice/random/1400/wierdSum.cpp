#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m;
	cin >> n >> m;

	unordered_map<int, vector<int>> cr;
	unordered_map<int, vector<int>> cc;

	int v;
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			cin >> v, cr[v].push_back(r), cc[v].push_back(c);

	int res = 0;
	vector<int> p(n * m + 1);
	for (auto &[c, vec] : cr) {
		int sz = vec.size();
		p[0] = 0;

		sort(vec.begin(), vec.end());
		for (int r = 1; r <= sz; r++)
			p[r] = p[r - 1] + vec[r - 1];

		for (int r = 0; r < sz; r++) 
			res += (p[sz] - p[r + 1]) - (sz - r - 1) * vec[r];
		
	}

	vector<int> q(n * m + 1, 0);
	for (auto &[c, vec] : cc) {
		int sz = vec.size();
		q[0] = 0;

		sort(vec.begin(), vec.end());
		for (int r = 1; r <= sz; r++)
			q[r] = q[r - 1] + vec[r - 1];

		for (int r = 0; r < sz; r++)
			res += (q[sz] - q[r + 1]) - (sz - r - 1) * vec[r]; 
	}

	cout << res << endl;
	return 0;
}