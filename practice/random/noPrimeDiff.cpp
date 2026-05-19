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
	} else {
		// both n and m are prime in this case (n, m >= 4)
		// so, if n is prime, then n - 1 >= 3 and is thus composite

		vector<int> p;
		for (int i = 1; i <= n; i += 2) p.push_back(i);
		for (int i = 2; i <= n; i += 2) p.push_back(i);
		
		int cur = 1;
		for (int r : p) 
			for (int c = 1; c <= m; c++) 
				mat[r][c] = cur++;
	}

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= m; c++)
			cout << mat[r][c] << " ";
		cout << endl;
	}
	cout << endl;
}

int32_t main() {
	nprime[0] = nprime[1] = true;
	for (int i = 2; i <= MAX; i++)
		if (!nprime[i])
			for (int j = i * i; j <= MAX; j += i)
				nprime[j] = true;
	int t; cin >> t;
	while (t--) solve();
	return 0;
}