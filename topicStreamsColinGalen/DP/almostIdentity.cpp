#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, k;
	cin >> n >> k;

	vector<vector<int>> C(n + 1, vector<int>(n + 1, 0));
	C[1][0] = C[1][1] = 1;
	for (int r = 2; r <= n; r++) {
		C[r][0] = 1;
		for (int s = 1; s <= r; s++)
			C[r][s] = C[r - 1][s] + C[r - 1][s - 1];
	}

	vector<int> D(k + 1, 0);
	D[0] = 1, D[1] = 0;
	for (int r = 2; r <= k; r++)
		D[r] = (r - 1) * (D[r - 1] + D[r - 2]);

	int res = 0;
	for (int m = n - k; m <= n; m++)
		res += C[n][m] * D[n - m];

	cout << res << endl;
	return 0;
}