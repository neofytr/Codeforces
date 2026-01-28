#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n;
	cin >> n;

	vector<int> arr(n + 1), last(n + 2);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	last[0] = LLONG_MIN;
	for (int r = 1; r <= n + 1; r++)
		last[r] = LLONG_MAX;

	// last[r] = smallest element that ends a strictly increasing
	// subsequence of length r for >= 1

	// Claim: last is always sorted in strictly increasing order
	// Proof: Suppose last[i] >= last[i + 1]
	// This means that there is a strictly increasing subsequence of length i + 1
	// that ends at last[i + 1]. The ith element of this subsequence (say x)
    // will be < last[i + 1]. Thus, there is a strictly increasing subsequence
	// of length i that ends at x < last[i], which is a contradiction.

	for (int r = 1; r <= n; r++) {
		int left = 0;
		int right = n + 1;

		// find the largest i such that last[i] < arr[r] for 0 <= i <= n
		while (right != left + 1) {
			int mid = left + (right - left) / 2;
			if (last[mid] < arr[r])
				left = mid;
			else 
				right = mid;
		}

		last[left + 1] = arr[r];
	}

	for (int r = n; r >= 1; r--)
		if (last[r] != LLONG_MAX) {
			cout << r << " ";
			break;
		}
	return 0;
}	