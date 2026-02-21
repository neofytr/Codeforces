#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(300)

int grid[MAX + 1][MAX + 1];
int p[MAX + 1][MAX + 1];
int32_t main() {
	int n, m, r, s;
	while (cin >> n >> m >> r >> s, n && m && r && s) {
		for (int row = 1; row <= n; row++)
			for (int col = 1; col <= m; col++)
				cin >> grid[row][col];

		for (int row = 1; row <= n; row++)
			for (int col = 1; col <= m; col++)
				p[row][col] += p[row][col - 1] + !grid[row][col];

		for (int i = 1; i <= m; i++)
			for (int j = i; j <= m; j++) {
				// we are trying to find the best row endings and startings
				// for the column endings [i, j]
				int up = 1;
				for (int down = 1; down <= n; down++)
			}
	}
}