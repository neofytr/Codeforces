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
	vector<int> L(n + 1, 0);

	// the invariant maintained in the dequeues is that at the beginning of every step, we contain
	// all the relevant minimums in decreasing order of indexes from back to the front of the queue
	for (int i = 1; i <= n; i++) {
		// we can safely remove any previous indexes that have values >= a[i] since
		// for any a[j] for j > i, either a[j] will be the minimum of the whole current a[1, i], or
		// if it is not, the value strictly less than it to its left won't be any of the removed values since
		// a[i] is less than all of the removed values anyway 
		while (!dq.empty() && a[dq.back()] >= a[i])
			dq.pop_back(); 
		if (!dq.empty())
			L[i] = dq.back();
		dq.push_back(i);
	}

	deque<int> q;
	vector<int> R(n + 1, n + 1);
	for (int i = n; i >= 1; i--) {
		// we can safely remove any previous indexes that have values > a[i] since for any a[j] for j < i, either
		// it will be the minimum of a[j, n] itself, or the value to its right that is less than or equal to it won't
		// be any of the removed values since they are larger than a[i] anyway
		while (!q.empty() && a[q.back()] > a[i])
			q.pop_back();
		if (!q.empty())
			R[i] = q.back();
		q.push_back(i);
	}

	int sum = 0;
	for (int i = 1; i <= n; i++)
		sum += a[i] * (i - L[i]) * (R[i] - i);

	int res = 0;
	for (int i = 1; i <= n; i++) {
		int mini = LLONG_MAX;
		for (int j = i; j <= n; j++)
			for (int k = i; k <= j; k++)
				mini = min(mini, a[k]);
		res += mini;
	}
	cout << sum << " " << res << endl;
	return 0;
}