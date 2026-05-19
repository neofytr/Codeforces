#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (1000)

vector<bool> nprime(MAX + 1);

void solve() {
	int n, m; cin >> n >> m;
	vector<vector<int>> mat(n + 1, vector<int>(m + 1));
	if (nprime[n]) {
		int s = 1;
		for (int c = 1; c <= m; c++)
			for (int r = 1; r <= n; r++)
				mat[r][c] = s++;
	} else if (nprime[m]) {
		int s = 1;
		for (int r = 1; r <= n; r++)
			for (int c = 1; c <= m; c++)
				mat[r][c] = s++;
	}
}

int32_t main() {
	nprime[0] = nprime[1] = true;
	for (int i = 2; i <= MAX; i++)
		if (!nprime[i])
			for (int j = i * i; j <= MAX; j++)
				nprime[j] = true;
	int t; cin >> t;
	while (t--) solve();
	return 0;
}