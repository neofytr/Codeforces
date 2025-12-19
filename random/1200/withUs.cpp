#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m;
	cin >> n >> m;

	int maxi = LLONG_MIN;
	vector<vector<int>> mat(n + 1, vector<int>(m + 1));
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++)
			cin >> mat[row][col], maxi = max(maxi, mat[row][col]);

	int cnt = 0;
	vector<pair<int, int>> mp;
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++)
			if (mat[row][col] == maxi)
				cnt++, mp.push_back({row, col});

	bool first = true, second = true;
	int r = mp[0].first;
	set<int> s1, s2;
	for (auto &[row, col] : mp)
		if (row != r)
			s1.insert(col);

	if (s1.size() > 1)
		first = false;

	int c = mp[0].second;
	for (auto &[row, col] : mp)
		if (col != c)
			s2.insert(row);

	if (s2.size() > 1)
		second = false;

	if (first || second)
		cout << maxi - 1 << endl;
	else 	
		cout << maxi << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}