#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define INF (int)(1e8)
#define MAX (int)(1e2)

int A[MAX + 1], B[MAX + 1];
int C[MAX + 1];
int dp[MAX + 1][MAX + 1][MAX * MAX + 1];

int32_t main() {
	int n;
	cin >> n;

	int sum = 0;
	for (int r = 1; r <= n; r++) cin >> A[r], sum += A[r];
	for (int r = 1; r <= n; r++) cin >> B[r], C[r] = B[r];

	int k = 0, s = 0;
	sort(C + 1, C + n + 1); 
	for (int r = n; r >= 1; r--)
		if (s < sum) s += C[r], k++;
		else break;

	// dp[r][c][m] is the minimum time required to pour m units of soda
	// into c bottles out of the first r bottles

	for (int r = 0; r <= n; r++)
		for (int c = 0; c <= n; c++)
			for (int m = 0; m <= MAX * MAX; m++)
				dp[r][c][m] = INF;

	dp[0][0][0] = 0;
	for (int r = 1; r <= n; r++) {
		dp[r][0][0] = 0;
		for (int c = 1; c <= min(r, k); c++) {
			dp[r][c][0] = 0;
			for (int m = 1; m <= MAX * MAX; m++) {
				// either i can use the rth bottle, or not use
				dp[r][c][m] = dp[r - 1][c][m]; // not use the rth bottle
				for (int last = 1; last <= min(m, B[r]); last++) // how much is poured into the last bottle?
					if (last <= A[r]) dp[r][c][m] = min(dp[r][c][m], dp[r - 1][c - 1][m - last]);
					else dp[r][c][m] = min(dp[r][c][m], dp[r - 1][c - 1][m - last] + (A[r] - last));
			}
		}
	}
	return 0;
}