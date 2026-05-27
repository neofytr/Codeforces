#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	// We are to calculate the sum of minimums of all the subarrays of a
	// For each 1 <= i <= n, we calculate the following

	// L[i] = the largest index 1 <= j < i such that a[j] < a[i]
	//  	= 0 if no such index exists

	// R[i] = the smallest index i < j <= n such that a[j] >= a[i]
	//  	= n + 1 if no such index exists

	// Then, for each 1 <= i <= n, the subarrays of a where a[i] is the minimum are a[r, s]
	// where L[i] + 1 <= r <= i and i <= s <= R[i] - 1, and thus their count is c[i] = (i - L[i]) * (R[i] - i)

	// Each subarray minimum is counted exactly once
	// Suppose a[i, j] is a subarray with the minimum b. Suppose k is the largest value of i <= x <= j
	// such that a[x] = b. Then, the minimum b will be counted exactly once, and that is in the count c[k]. If there are 
	// other indexes in [i, j] that are less than k but with value b, their c values don't include this subarray
	// since all their R values stop just shy of the first equal value on the right.

	deque<int> dq;
	vector<int> L(i + 1, 0);


	return 0;
}