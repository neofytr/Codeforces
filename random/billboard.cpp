#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(300)

int grid[MAX + 1][MAX + 1];
int p[MAX + 1][MAX + 1];

int32_t main() {
	int n, m, r, s;
	while (cin >> n >> m >> r >> s) {
		if (!n && !m && !r && !s) return 0;

		for (int row = 1; row <= n; row++)
			for (int col = 1; col <= m; col++)
				cin >> grid[row][col];

		for (int row = 1; row <= n; row++) {
			p[row][0] = 0;
			for (int col = 1; col <= m; col++)
				p[row][col] = p[row][col - 1] + !grid[row][col];
		}

		int maxi = 0;

		for (int i = 1; i <= m; i++) {
			for (int j = i; j <= m; j++) {

				if (!r) {
					int up = 1, sum = 0;
					for (int down = 1; down <= n; down++) {
						int cost = p[down][j] - p[down][i - 1];
						sum += cost;
						while (up <= down && sum > s) {
							sum -= (p[up][j] - p[up][i - 1]);
							up++;
						}
						if (up <= down)
							maxi = max(maxi, (down - up + 1) * (j - i + 1));
					}
					continue;
				}

				int up = 1;
				multiset<int> s1, s2;
				int sum = 0;

				for (int down = 1; down <= n; down++) {
					int cost = p[down][j] - p[down][i - 1];

					if ((int)s2.size() < r) {
						s2.insert(cost);
					} else {
						int mini = *s2.begin();
						if (cost > mini) {
							s2.erase(s2.begin());
							s2.insert(cost);
							s1.insert(mini);
							sum += mini;
						} else {
							s1.insert(cost);
							sum += cost;
						}
					}

					while (up <= down && sum > s) {
						int rem = p[up][j] - p[up][i - 1];
						auto it = s2.find(rem);
						if (it != s2.end()) {
							s2.erase(it);
							int t = *s1.rbegin();
							s1.erase(prev(s1.end()));
							sum -= t;
							s2.insert(t);
						} else {
							s1.erase(s1.find(rem));
							sum -= rem;
						}
						up++;
					}

					if (up <= down)
						maxi = max(maxi, (down - up + 1) * (j - i + 1));
				}
			}
		}

		cout << maxi << '\n';
	}
	return 0;
}