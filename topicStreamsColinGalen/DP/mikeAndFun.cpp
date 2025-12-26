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

	vector<vector<bool>> hasStart(n + 1, vector<bool>(m + 1, false));
	vector<vector<int>> lenStart(n + 1, vector<int>(m + 1, 0));
	vector<vector<bool>> hasEnd(n + 1, vector<bool>(m + 1, false));
	vector<vector<int>> lenEnd(n + 1, vector<int>(m + 1, 0));
	vector<set<pair<int, int>>> starting(n + 1);
	vector<set<pair<int, int>>> ending(n + 1);
	for (int r = 1; r <= n; r++) {
		vector<int> &v = mat[r];
		int i = 1, j = 1;

		while (i <= m) {
			if (!v[i]) {
				i++;
				continue;
			}

			j = i;
			while (j <= m && v[j])
				j++;

			hasStart[r][i] = true, starting[r].insert({j - i, i}), lenStart[r][i] = j - i;
			hasEnd[r][j - 1] = true, ending[r].insert({j - i, j - 1}), lenEnd[r][j - 1] = j - i;
			j = i;
		}
	}

	int i, j;
	while (q--) {
		cin >> i >> j;

		if (!mat[i][j]) {
			if (j >= 2 && hasEnd[i][j - 1]) {
				int lenend = lenEnd[i][j - 1];

			}
		}
			
		
	}
}