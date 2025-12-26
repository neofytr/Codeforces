#include <bits/stdc++.h>
using namespace std;

#define int long long 


int32_t main() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<vector<int>> mat(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			cin >> mat[r][c];

	set<pair<int, pair<int, int>>> s;
	vector<vector<pair<int, int>>> where(n + 1, vector<pair<int, int>>(m + 1, {-1, -1}));
	for (int r = 1; r <= n; r++) {
		vector<int> &v = mat[r];

		int i = 1, j = 1;
		while (i <= j) {
			if (!v[i]) {
				i++;
				continue;
			}

			while (j <= m && v[j])
				j++;

			int len = j - i, start = i;
			for (int k = i; k < j; k++)
				where[r][k] = {start, len};
			s.insert({len, {r, i}});
			j = i;
		}
	}

	int i, j;
	while (q--) {
		cin >> i >> j;
	}
}