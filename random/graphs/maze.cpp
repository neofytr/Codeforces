#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m, k; cin >> n >> m >> k;
	vector<vector<int>> grid(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++) {
		string col; cin >> col;
		for (int c = 1; c <= m; c++) {
			grid[r][c] = ((col[c - 1] == '.') ? 0 : 1);
		}
 	}

 	int dr[] = {-1, 0, 1, 0};
 	int dc[] = {0, -1, 0, 1};
 	
}