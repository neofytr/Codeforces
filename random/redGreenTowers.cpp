#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MOD (int)(1e9 + 7)

int f(int x) {
	return (x * (x + 1)) / 2;
}

int32_t main() {
	int r, g;
	cin >> r >> g;

	// r, g >= 0 and r + g >= 1
	// Define f(x) = 1 + ... + x for all x >= 1

	// Let x >= 1
	// Let A = {1, 2, ..., x}
	// For any 0 <= s <= (x * (x + 1)) / 2, there is a subset of A with sum s
	// No other subset sum is possible

	// It is possible to form a pyramid of height x 
	// iff there is a subset of A (say B) such that sum(B) <= r and f(x) - sum(B) <= g
	// iff there is a subset of A (say B) such that f(x) - g <= sum(B) <= r
	// iff f(x) <= r + g
	// Proof of the last equivalence:
	// For any subset B of A, sum(B) is in the range [0, f(x)] and can take
	// any value in that range
	// Thus if f(x) <= r + g, i.e, f(x) - g <= r, the ranges [0, f(x)] and [f(x) - g, r] 
	// have an intersection (since g >= 0), and thus there is a subset B of A that
	// has its sum equal to that intersection and thus f(x) - g <= sum(B) <= r holds
	// Now, if f(x) - g > r, there is no possible value of sum(B)

	int left = 1;
	int right = r + g + 1;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if ((mid * (mid + 1)) / 2 <= r + g)
			left = mid;
		else
			right = mid;
	}

	int maxht = left;

	vector<int> dp(r + 1, 0);
	dp[0] = 1;

	for (int height = 1; height <= maxht; height++) 
		for (int red = r; red >= height; red--) 
			dp[red] = (dp[red] + dp[red - height]) % MOD;
		

	int cnt = 0;
	for (int red = 0; red <= r; red++)
		if (f(maxht) <= red + g)
			cnt = (cnt + dp[red]) % MOD;

	cout << cnt << endl;

	/*
	// dp[i][j] is the number of pyramids possible of height i using j red blocks
	vector<vector<int>> dp(maxht + 1, vector<int>(r + 1, 0));

	dp[0][0] = 1;
	for (int height = 1; height <= maxht; height++)
		for (int red = 0; red <= r; red++)
			// either the base row will be red or green
			if (red >= height)
				dp[height][red] = (dp[height - 1][red] + dp[height - 1][red - height]) % MOD;
			else 
				dp[height][red] = dp[height - 1][red];

	int cnt = 0;
	for (int red = 0; red <= r; red++)
		if (f(maxht) <= red + g)
			cnt += dp[maxht][red];

	cout << cnt << endl;
	*/

	return 0;
}
