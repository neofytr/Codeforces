#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;
	char c;
	vector<vector<int>> grid(n + 1, vector<int>(m + 1));

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cin >> c;
			switch(c) {
			case '.': 
				grid[i][j] = 0;
				break; // empty
			case '*': 
				grid[i][j] = 1;
				break; // stone
			case 'o': 
				grid[i][j] = 2;
				break; // obstacle
			default: grid[i][j] = 3;
			}
		}

	vector<priority_queue<int>> emp(m + 1);
	for (int j = 1; j <= m; j++)
		for (int i = 1; i <= n; i++)
			if (!grid[i][j])
				emp[j].push(i);

	vector<vector<int>> final(n + 1, vector<int>(m + 1));
	for (int j = 1; j <= m; j++)
		for (int i = n; i >= 1; i--)
			if (grid[i][j] == 1) {
				if (emp[j].empty()) {
					final[i][j] = grid[i][j] = 1;
					continue;
				}
				int f = emp[j].top(); 
				if (f < i) {
					final[i][j] = 1;
					continue;
				}
				emp[j].pop(); emp[j].push(i);
				final[f][j] = grid[f][j] = 1, final[i][j] = grid[i][j] = 0;
			} else if (grid[i][j] == 2) {
				final[i][j] = 2;
				while (!emp[j].empty() && emp[j].top() >= i) emp[j].pop();
			} else final[i][j] = grid[i][j];

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) 
			if (!final[i][j])
				cout << '.';
			else if (final[i][j] == 1)
				cout << '*';
			else cout << 'o';
		cout << endl;
	}

	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}