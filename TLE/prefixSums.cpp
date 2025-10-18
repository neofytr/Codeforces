#include <bits/stdc++.h>
using namespace std;

#define int long long

void twoDim() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> arr(n, vector<int>(m));
	for (int row = 0; row < n; row++)
		for (int col = 0; col < m; col++)
			cin >> arr[row][col];

	// prefix[r][c] = sum of all the values in the rectangle
	// with diagonal end points (0, 0) and (r - 1, c - 1) in the array arr for n >= r >= 1, m >= c >= 1
	// prefix[r][0] = 0 for all 0 <= r <= n
	// prefix[0][c] = 0 for all 0 <= c <= m
	vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));

	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++)
			prefix[row][col] = prefix[row - 1][col] + prefix[row][col - 1] - prefix[row - 1][col - 1] + arr[row - 1][col - 1];

	int x1, x2, y1, y2;
	int q;
	cin >> q;
	while(q--) {
		// 0 <= y1 <= y2 < n
		// 0 <= x1 <= x2 < m
		// we want to find the sum of the rectangle with diagonal end points (y1, x1) and (y2, x2)
		// in the array arr

		cin >> y1 >> x1 >> y2 >> x2;
		cout << prefix[y2 + 1][x2 + 1] - prefix[y1][x2 + 1] - prefix[y2 + 1][x1] + prefix[y1][x1] << endl;
	}
	return;
}
 
int32_t main() {
	int n;
	cin >> n;

	vector<int> arr(n);
	for (int &val : arr)
		cin >> val;

	// for all 0 <= r <= n, prefix[r] is the sum of first r elements of the array arr
	// prefix[0] = 0;
	// prefix[r] = summation from i = 0 to i = r - 1 of arr[i], for all 1 <= r <= n
	vector<int> prefix(n + 1, 0);

	// for all 1 <= r <= n, prefix[r] = prefix[r - 1] + arr[r - 1]
	for (int r = 1; r <= n; r++)
		prefix[r] = prefix[r - 1] + arr[r - 1];

	int l, r;
	int q;
	cin >> q;
	while(q--) {
		cin >> l >> r;

		// 0 <= l <= r < n
		// we want the sum of arr[l, r]
		// arr[l, r] = arr[l] + ... + arr[r]
		// There are two cases
		// 1. l >= 1
		// arr[l, r] = (arr[0] + ... + arr[r]) - (arr[0] + ... + arr[l - 1])
		// 			 = prefix[r + 1] - prefix[l]
		// 2. l = 0
		// arr[l, r] = arr[0, r] = prefix[r + 1] - 0 = prefix[r + 1] - prefix[0]
		// 											 = prefix[r + 1] - prefix[l]

		// Thus, for 0 <= l <= r < n, arr[l, r] = prefix[r + 1] - prefix[l]
		cout << prefix[r + 1] - prefix[l] << endl;
	}
	return 0;
}