#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve(int n, int k) {
	int test = k;

	// exactly k pairs of (l, r) where 1 <= l <= r <= n such that
	// sum[l, r] > 0, i.e., p[r] > p[l - 1]

	int d = n;
	vector<int> arr(n + 1, 0);
	while (k && k >= d) {
		k -= d;
		arr[d] = 1000;
		d--;
	}

	if (k) {
		arr[k] = 900;
		arr[k + 1] = -910;
	}
	
	for (int i = 1; i <= n; i++)
		if (!arr[i])
			arr[i] = -1;

	for (int r = 1; r <= n; r++)
		cout << arr[r] << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		int n, k;
		cin >> n >> k;

		if (!k) {
			for (int r = 1; r <= n; r++)
				cout << -1 << " ";
			cout << endl;
			continue;
		}
		solve(n, k);
	}
	return 0;
}