#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(1e2)
#define TMAX (int)(20 * 100)

int t[MAX + 1], b[MAX + 1], v[MAX + 1];
int dp[MAX + 1][TMAX + 1];
pair<int, int> vec[MAX + 1];
int32_t main() {
	int n;
	cin >> n;

	for (int r = 1; r <= n; r++)
		cin >> t[r] >> b[r] >> v[r];

	int sz = 0;
	for (int r = 1; r <= n; r++)
		if (b[r] >= t[r]) vec[++sz] = {b[r] - t[r], r};

	if (!sz) {
		cout << 0 << endl;
		cout << 0 << endl;
		return 0;
	}
	sort(vec + 1, vec + sz + 1);

	// dp[i][j] is the maximum value we can get out of the saved items in vec[1, i]
	// with total time spent = j

	return 0;
}