#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define INF (int)(1e8)
#define MAX (int)(1e2)

int A[MAX + 1], B[MAX + 1];
int C[MAX + 1];
int dp[2][MAX + 1][MAX * MAX + 1];
int prefOne[MAX + 1][MAX * MAX + 1], prefTwo[MAX + 1][MAX * MAX + 1];

template<typename T>
class SparseTable {
private:
	// table[r][j] = minimum of the range [arr[r], ..., arr[r + (1LL << j) - 1]] 
	// for 0 <= j <= LOG2(MAX_N) and 1 <= r <= (MAX_N + 1 - (1LL << j))
	vector<vector<T>> table;
	function<T(T, T)> op;

public:
	// table[r][j] = min(table[r][j - 1], table[r + (1LL << (j - 1))][j - 1]) 
	// table[r][0] = arr[r] 
	SparseTable(vector<T> &arr, function<T(T, T)> operation) {
		int n = (int)arr.size(); // 1-based indexed array
		n--;
		if (!n) return; // handle empty case

		int lg = LOG2(n);
		table.resize(n + 1, vector<T>(lg + 1));

		op = operation;
		// build base case for j = 0
		for (int r = 1; r <= n; r++)
			table[r][0] = arr[r];

		// build sparse table for higher powers of 2
		for (int j = 1; j <= lg; j++)
			for (int r = 1; r <= (n + 1 - (1LL << j)); r++)
				table[r][j] = op(table[r][j - 1], table[r + (1LL << (j - 1))][j - 1]);
	}

	// query the minimum value in range [l, r] (1-based indexing)
	int query(int l, int r) {
		int lg = LOG2(r - l + 1);
		// min of the two overlapping intervals covering [l, r]
		return op(table[l][lg], table[r - (1LL << lg) + 1][lg]);
	}
};

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
			for (int m = 1; m <= sum; m++) {
				// either i can use the rth bottle, or not use it
				dp[curr][c][m] = dp[prev][c][m];
				for (int last = 1; last <= min(m, B[r]); last++) 
					if (last <= A[r]) dp[curr][c][m] = min(dp[curr][c][m], dp[prev][c - 1][m - last]);
					else dp[curr][c][m] = min(dp[curr][c][m], dp[prev][c - 1][m - last] + (last - A[r]));
			}
		}

		for (int c = 0; c <= k - 1; c++)

	}

	cout << dp[curr][k][sum] << endl;
	return 0;
}