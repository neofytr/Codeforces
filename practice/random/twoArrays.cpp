#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MOD (int)(1e9 + 7)

int32_t main() {
	int n, m;
	cin >> n >> m;

	// Number of pairs of arrays (a, b) such that
	// 1. a is sorted in increasing order
	// 2. b is sorted in decreasing order
	// 3. length of both arrays is m
	// 4. each element of each array is an integer in the range [1, n]
	// 5. a[r] <= b[r] for all 1 <= r <= m

	// Number of pairs of integer arrays (a, b) of length m such that
	// n >= b[1] >= b[2] >= ... >= b[m - 1] >= b[m] >= a[m] >= a[m - 1] >= ... >= a[1] >= 1

	// We have to find the number of ways to fill these 2 * m places in the
	// specified order with elements from the multiset [1, n]

	// This can be done very easily
	// Let xr is the number of rs we have for 1 <= r <= n
	// Then, for each solution of x1 + ... + xn = 2 * m, we have exactly
	// one way to place the 2m integers (in decreasing order)
	// So, the answer is C(2 * m + n - 1, n - 1)

	// First we select the number of different elements in these 2 * m places, say d,
	// where 1 <= d <= min(2 * m, n)
	// The number of ways to select d different elements is C(n, d)
	// After selecting these d different elements, we have to make duplicates of them
	// so that the total number of elements is 2 * m
	// The number of ways to do this is the number of positive integral solutions
	// of x1 + ... + xd = 2 * m, which is C(2 * m - 1, d - 1)
	// Now for each of these solutions, which has total 2 * m elements (d distinct and rest duplicates
	// of these distinct), there is exactly one way to place these in the 2 * m places since we have to
	// place the elements in decreasing order

	// Thus, the total answer is
	// cnt = 0
	// for (d = 1; d <= min(2 * m, n); d++) cnt += C(n, d) * C(2 * m - 1, d - 1)

	vector<vector<int>> dp(max(n, 2 * m) + 1, vector<int> (max(n, 2 * m) + 1, 0));
	dp[0][0] = 1;
	for (int i = 1; i <= max(n, 2 * m); i++) {
		dp[i][i] = dp[i][0] = 1;
		for (int j = 1; j <= i - 1; j++)
			dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
	}
	int cnt = 0;
	for (int d = 1; d <= min(2 * m, n); d++) 
		cnt = (cnt + dp[n][d] * dp[2 * m - 1][d - 1] % MOD) % MOD;
	cout << cnt << endl;
	return 0;
}