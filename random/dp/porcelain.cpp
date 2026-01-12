#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m;
	cin >> n >> m;

	int sz;
	vector<vector<int>> mat(n + 1);
	for (int r = 1; r <= n; r++) {
		cin >> sz;
		mat[r].resize(sz + 1);
		for (int c = 1; c <= sz; c++)
			cin >> mat[r][c];
	}

	vector<vector<int>> p(n + 1);
	for (int r = 1; r <= n; r++) {
		sz = mat[r].size();
		p[r].resize(sz + 1);

		p[r][0] = 0;
		for (int c = 1; c <= sz; c++)
			p[r][c] += p[r][c - 1] + mat[r][c];
	}

	vector<vector<int>> maxi(n + 1);
	for (int r = 1; r <= n; r++) {
		sz = mat[r].size();
		maxi[r].resize(sz + 1);

		for (int alpha = 0; alpha <= sz; alpha++) {
			maxi[r][alpha] = LLONG_MIN;
			for (int l = 0; l <= alpha; l++)
				maxi[r][alpha] = max(maxi[r][alpha], p[r][l] + p[r][sz] - p[r][alpha - l - 1]);
		}
	}

	for (int r = 1; r <= n; r++) {
		for (int a = 0; a <= mat[r].size(); a++)
			cout << maxi[r][a] << " ";
		cout << endl;
	}
	return 0;
}