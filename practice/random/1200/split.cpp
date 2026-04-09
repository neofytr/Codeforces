#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> arr(n + 1), f(n + 1, 0);
	for (int r = 1; r <= n; r++) cin >> arr[r], f[arr[r]]++;

	for (int r = 1; r <= n; r++)
		if (f[r] % k) {
			cout << 0 << endl;
			return;
		} else f[r] = f[r] / k; // quantity in each ms

	// for a subarray arr[l, r] for 1 <= l <= r <= n to be awesome, it is
	// necessary and sufficient that the count of g in arr[l, r] is <= f[g] for 
	// all 1 <= g <= n

	// So, the property awesome is subsegment monotonic
	int cnt = 0;
	int l = 1;
	vector<int> qty(n + 1);
	for (int r = 1; r <= n; r++) {
		int elt = arr[r];
		qty[elt]++;

		while (l <= r && qty[elt] > f[elt])
			qty[arr[l++]]--;
		if (l <= r)
			cnt += (r - l + 1);
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}