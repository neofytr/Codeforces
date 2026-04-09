#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m, k; cin >> n >> m >> k;
	vector<int> a(n + 1), b(m + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= m; r++) cin >> b[r];

	int cnt = 0;
	vector<int> cons(n + 1);
	int i = 1, j = 1;
	while (i <= n) {
		while (i <= n && !a[i]) i++;

		j = i;
		while (j <= n && a[j])
			j++;

	 	// [i, j - 1]
		int len = j - i;
		int x = 1;
		for (int r = len; r >= 1; r--)
			cons[r] += x, x++;

		i = j;
	}

	i = 1, j = 1; 
	while (i <= m) {
		while (i <= m && !b[i]) 
			i++;
		
		j = i;
		while (j <= m && b[j])
			j++;

	 	// [i, j - 1]
		int len = j - i;
		int x = 1;
		for (int r = len; r >= 1; r--) {
			if (!(k % r)) {
				int d = k / r;
				if (d <= n)
					cnt += x * cons[d];
			}
			x++;
		}

		i = j;
	}

	cout << cnt << endl;
	return 0;
}