#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	while (m--) {
		int i, v;
		cin >> i >> v;
		i++;

		// update the value of a[i] to v and find m = maximum sum on any segment
		// of the array

		// output max(0, m)
	}
}