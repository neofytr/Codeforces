#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define INF (int)(1e8)
#define MAX (int)(1e2)

int A[MAX + 1], B[MAX + 1];
int C[MAX + 1];
int dp[2][MAX + 1][MAX * MAX + 1];

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

	for (int c = 0; c <= n; c++)
		for (int m = 0; m <= sum; m++)
			dp[0][c][m] = dp[1][c][m] = INF;

	dp[0][0][0] = 0;
	int prev = 1, curr = 0;
	for (int r = 1; r <= n; r++) {
		prev = prev ^ 1, curr = curr ^ 1;
		for (int c = 1; c <= k; c++) {
			dp[curr][c][0] = 0; 
			deque<int> d1, d2;

			for (int m = 1; m <= sum; m++) {
				
			}
		}
	}

	cout << dp[curr][k][sum] << endl;
	return 0;
}