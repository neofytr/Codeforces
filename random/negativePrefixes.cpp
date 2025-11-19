#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	vector<int> l(n + 1);
	vector<int> un;
	for (int r = 1; r <= n; r++) {
		cin >> l[r];
		if (!l[r])
			un.push_back(arr[r]);
	}

	int i = 0;
	sort(un.rbegin(), un.rend());
	for (int r = 1; r <= n; r++)
		if (!l[r])
			arr[r] = un[i++];

	for (int r = 1; r <= n; r++)
		cout << arr[r] << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}

	return 0;
}