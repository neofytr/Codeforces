#include <bits/stdc++.h>
using namespace std;

#define int long long

int dr[] = {-1, 0, 1, 0, -1, 1, -1, 1};
int dc[] = {0, -1, 0, 1, -1, 1, 1, -1};

int32_t main() {
	vector<vector<char>> graph(140, vector<char>(140));

	for (int row = 1; row <= 139; row++)
		for (int col = 1; col <= 139; col++)
			cin >> graph[row][col];

	int res = 0;
	while (true) {
		vector<pair<int, int>> collecn;
		for (int row = 1; row <= 139; row++)
			for (int col = 1; col <= 139; col++) {
				if (graph[row][col] != '@')
					continue;
				int cnt = 0;
				for (int i = 0; i < 8; i++) {
					int r = row + dr[i];
					int c = col + dc[i];
	
					if (r <= 139 && r >= 1 && c <= 139 && c >= 1 && graph[r][c] == '@')
						cnt++;
				}
				if (cnt <= 3)
					collecn.push_back({row, col});
			}

		if (collecn.empty())
			break;

		res += collecn.size();
		for (auto &[r, c] : collecn)
			graph[r][c] = 'x';
	}
	cout << res << endl;
}