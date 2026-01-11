#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(1e2)
#define INF (int)(1e8)

int A[MAX + 1], B[MAX + 1], t[MAX + 1];
int cpy[MAX + 1];
int dp[MAX + 1][MAX + 1][MAX * MAX + 1];

int32_t main() {
	int n;
	cin >> n;

	for (int r = 1; r <= n; r++) cin >> A[r];
	for (int r = 1; r <= n; r++) cin >> B[r], cpy[r] = B[r];
	for (int r = 1; r <= n; r++) t[r] = B[r] - A[r];

	int sum = 0;
	for (int r = 1; r <= n; r++) sum += A[r];
	sort(cpy + 1, cpy + n + 1);

	int x = 0, s = 0;
	for (int r = n; r >= 1; r--)
		if (s + cpy[r] >= sum) {
			x++;
			break;
		} else s += cpy[r], x++;
		
	// dp[r][s][t] is the minimum time to pour t units of soda into s bottles 
	// in the range [1, r]

	for (int r = 0; r <= MAX; r++)
		for (int s = 0; s <= MAX; s++)
			for (int t = 0; t <= MAX * MAX; t++)
				dp[r][s][t] = INF;

	dp[0][0][0] = 0;
	for (int r = 1; r <= n; r++) {
		dp[r][0][0] = 0;
		for (int s = 1; s <= min(x, r); s++) {
			dp[r][s][0] = 0;
			for (int t = 1; t <= MAX * MAX; t++) {
				dp[r][s][t] = dp[r - 1][s][t];
				for (int last = 1; last <= min(t, B[r]); last++)
					if (last <= A[r])
						dp[r][s][t] = min(dp[r][s][t], dp[r - 1][s - 1][t - last]);
					else dp[r][s][t] = min(dp[r][s][t], dp[r - 1][s - 1][t - last] + last - A[r]);
			}
		}
	}

	cout << x << " ";
	int mini = LLONG_MAX;
	for (int s = sum; s <= MAX * MAX; s++)
		mini = min(mini, dp[n][x][s]);
	cout << mini << endl;
	return 0;
}