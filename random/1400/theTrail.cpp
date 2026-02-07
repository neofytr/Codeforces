#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
	int deg, type, idx;
	bool operator>(const Node& other) const {
		return deg > other.deg;
	}
};

void solve() {
	int n, m; cin >> n >> m;
	string path; cin >> path;

	vector<vector<int>> grid(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			cin >> grid[r][c];

	vector<int> rowsums(n + 1, 0), colsums(m + 1, 0);
	vector<set<int>> rowvars(n + 1), colvars(m + 1);

	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++) {
			rowsums[r] += grid[r][c];
			colsums[c] += grid[r][c];
		}

	// build path cells
	int x = 1, y = 1;
	rowvars[x].insert(y);
	colvars[y].insert(x);
	for (char ch : path) {
		if (ch == 'R') x++;
		else y++;
		rowvars[y].insert(x);
		colvars[x].insert(y);
	}

	priority_queue<Node, vector<Node>, greater<Node>> pq;

	for (int r = 1; r <= n; r++)
		if (!rowvars[r].empty())
			pq.push({(int)rowvars[r].size(), 0, r});

	for (int c = 1; c <= m; c++)
		if (!colvars[c].empty())
			pq.push({(int)colvars[c].size(), 1, c});

	while (!pq.empty()) {
		auto [deg, type, i] = pq.top();
		pq.pop();

		if (type == 0 && (int)rowvars[i].size() != deg) continue;
		if (type == 1 && (int)colvars[i].size() != deg) continue;

		if (type == 0) {
			// row
			int inc = -rowsums[i];
			rowsums[i] = 0;

			for (int c : rowvars[i]) {
				grid[i][c] = inc;
				colsums[c] += inc;
				colvars[c].erase(i);
				if (!colvars[c].empty())
					pq.push({(int)colvars[c].size(), 1, c});
			}
			rowvars[i].clear();
		} else {
			// column
			int inc = -colsums[i];
			colsums[i] = 0;

			for (int r : colvars[i]) {
				grid[r][i] = inc;
				rowsums[r] += inc;
				rowvars[r].erase(i);
				if (!rowvars[r].empty())
					pq.push({(int)rowvars[r].size(), 0, r});
			}
			colvars[i].clear();
		}
	}

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= m; c++)
			cout << grid[r][c] << " ";
		cout << '\n';
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
}
