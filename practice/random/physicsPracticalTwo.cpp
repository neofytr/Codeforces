#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	// subsegment monotonic
	int len = LLONG_MIN;
	sort(arr.begin(), arr.end());
	int l = 1;
	for (int r = 1; r <= n; r++) {
		while (l <= r && arr[r] > 2 * arr[l])
			l++;

		if (l <= r)
			len = max(len, r - l + 1);
	}

	cout << n - len << endl;
	return 0;
}