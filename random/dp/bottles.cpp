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
		dp[curr][0][0] = 0;
		for (int c = 1; c <= k; c++) {
			dp[curr][c][0] = 0; 
			deque<int> d1, d2;
			for (int m = 1; m <= sum; m++) {
				int beta = min(m, A[r]);
				int L = m - beta, R = m - 1; 
				// l never decreses and r increases by 1 at each step
				// So, we can use a monotonic deque for range minimum

				dp[curr][c][m] = dp[prev][c][m];
				while (!d1.empty() && dp[prev][c - 1][d1.back()] >= dp[prev][c - 1][R])
					d1.pop_back();
				d1.push_back(R);

				while (!d1.empty() && d1.front() < L)
					d1.pop_front();
				
				dp[curr][c][m] = min(dp[curr][c][m], dp[prev][c - 1][d1.front()]);
				
				L = m - min(m, B[r]), R = m - beta;
				while (!d2.empty() && dp[prev][c - 1][d2.back()] - d2.back() >= dp[prev][c - 1][R] - R)
					d2.pop_back();
				d2.push_back(R);

				while (!d2.empty() && d2.front() < L)
					d2.pop_front();

				dp[curr][c][m] = min(dp[curr][c][m], dp[prev][c - 1][d2.front()] - d2.front() + m - A[r]);
			}
		}
	}

	cout << k << " ";
	cout << dp[curr][k][sum] << endl;
	return 0;
}