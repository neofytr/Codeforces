#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n);
	for (int &val : arr)
		cin >> val;

	int i = 0, j = 0;
	int x = n;
	while(i < n) {
		j = i;
		int j1 = j, j2 = j; 
		while (j1 < n - 1 && arr[j1] >= arr[j1 + 1])
			j1++;
		while(j2 < n - 1 && arr[j2] <= arr[j2 + 1])
			j2++;

		int len = max(j2 - i + 1, j1 - i + 1);
		if (len == 1)
			break;
		if (len == 2) {
			if (arr[i] == arr[max(j2, j1)])
				x--;
			i = max(j2, j1);
			continue;
		}
		x -= (len - 2);
		i = max(j1, j2);
	}

	if (x == 2 && arr[0] == arr[n - 1])
		x--;

	cout << x << endl;
}

int32_t main() {
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}