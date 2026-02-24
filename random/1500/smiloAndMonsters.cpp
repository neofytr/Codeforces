#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	sort(arr.begin() + 1, arr.end());
	int l = 1, r = n;

	int cnt = 0;
	while (l < r) {
		int sum = 0;
		while (l < r && sum + arr[l] <= arr[r])
			sum += arr[l++];
		l--;
		if (l == r - 1) {
			arr[r] -= sum;
			cnt += (sum + 1);
			cnt += (arr[r] + 1) / 2;
			break;
		}

		if (sum == arr[r]) {
			cnt += (sum + 1);
			l++, r--;
			continue;
		}

		int e = arr[r] - sum;
		arr[l + 1] -= e;
		cnt += (arr[r] + 1);
		l++, r--;
	}

	if (l == r) 
		if (!(arr[l] & 1)) cnt += ((arr[l] / 2) + 1);
		else if (arr[l] < 5) cnt += (arr[l]);
		else cnt += ((arr[l] / 2) + 2);

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}