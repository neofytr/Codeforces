#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, x;
	cin >> n >> x;

	int val;
	vector<pair<int, int>> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> val, arr[r] = {val, r};

	sort(arr.begin() + 1, arr.end());
	for (int i = 1; i <= n; i++) {
		int xdash = x - arr[i].first;
		int j = i + 1, k = n;
		while (k > j)
			if (arr[j].first + arr[k].first > xdash)
				k--;
			else if (arr[j].first + arr[k].first < xdash)
				j++;
			else {
				cout << arr[i].second << " " << arr[j].second << " " << arr[k].second << endl;
				return 0;
			}
	}

	cout << "IMPOSSIBLE" << endl;
	return 0;
}