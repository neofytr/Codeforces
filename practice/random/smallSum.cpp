#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, s;
	cin >> n >> s;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	int cnt = 0;
	int sum = 0;
	int l = 1;
	for (int r = 1; r <= n; r++) {
		sum += arr[r];
		while (l <= r && sum > s)
			sum -= arr[l++];
		if (l <= r)
			cnt += (r - l + 1);
	}

	cout << cnt << endl;
	return 0;
}