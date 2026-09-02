#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, q; cin >> n >> q;
	vector<pair<int, int>> arr(n + 1);
	for (int i = 1; i <= n; i++) cin >> arr[i].first, arr[i].second = 0;

	int latest_x = 0, latest_time = 0;
	int sum = 0;
	for (int i = 1; i <= n; i++) 
		sum += arr[i].first;
	int k = 0;
	while (q--) {
		k++;
		int t, i, x; cin >> t;
		if (t == 1) {
			cin >> i >> x;
			if (latest_time > arr[i].second)
				sum -= latest_x;
			else  
				sum -= arr[i].first;
			sum += x;
			arr[i].first = x, arr[i].second = k;
			cout << sum << endl;
		} else {
			cin >> x;
			latest_x = x, latest_time = k;
			sum = n * x;
			cout << sum << endl;
		}
	}
	return 0;
}