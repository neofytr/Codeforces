#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(5 * 1e2)

int c[MAX + 1];
bool dp[MAX + 1][MAX + 1];

int32_t main() {
	int n, k;
	cin >> n >> k;

	for (int r = 1; r <= n; r++) cin >> c[r];

	dp[0][0] = true;
	for (int r = 1; r <= n; r++)
		for (int i = k; i >= 0; i--)
			for (int j = i; j >= 0; j--) {
				// the current element, r, has three choices
				// 1. it can go only in the subset
				// 2. it can go both in the subset and the sub-subset
				// 3. it goes nowhere (not selected)
				bool ok = dp[i][j]; 
				if (i >= c[r]) ok |= dp[i - c[r]][j];
				if (i >= c[r] && j >= c[r]) ok |= dp[i - c[r]][j - c[r]];
				dp[i][j] = ok;
			}

	set<int> res;
	for (int j = 0; j <= k; j++)
		if (dp[k][j]) res.insert(j);
	cout << res.size() << endl;
	for (int e : res)
		cout << e << " ";
	cout << endl;
}

int32_t main2() {
	int n, k;
	cin >> n >> k;

	for (int r = 1; r <= n; r++)
		cin >> c[r];

	// create dp[MAX + 1][MAX + 1][MAX + 1] for this to work
	int dp[1][1][1];

	// dp[r][i][j] is true iff there is a subset of c[1, r] that has a sum i, that
	// has a subset that has a sum j
	for (int r = 0; r <= n; r++)
		for (int i = 0; i <= k; i++)
			for (int j = 0; j <= k; j++)
				dp[r][i][j] = false;

	dp[0][0][0] = true;
	for (int r = 1; r <= n; r++) 
		for (int i = 0; i <= k; i++)
			for (int j = 0; j <= i; j++) { // either we do not use the rth element, or we put the rth element only in the main subset, or we put the rth element in both the main
				// and the sub-subset
                bool ok = dp[r - 1][i][j];
                if (i >= c[r])
                  ok |= dp[r - 1][i - c[r]][j]; 
                if (i >= c[r] && j >= c[r])
                  ok |= dp[r - 1][i - c[r]][j - c[r]]; 
                dp[r][i][j] = ok;
			}
				

	set<int> res;
	for (int j = 0; j <= k; j++)
		if (dp[n][k][j]) res.insert(j);

	cout << res.size() << endl;
	for (const int e : res)
		cout << e << " ";
	cout << endl;
	return 0;
}
