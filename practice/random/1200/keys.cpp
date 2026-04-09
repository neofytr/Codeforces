#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, x;
	cin >> n >> x;

	if (n == 1) {
		cout << x << endl;
		return;
	}

	vector<int> arr;
	bool stop = false;
	for (int r = 0; r <= n - 2 && !stop; r++) {
		for (int bit = 0; bit <= 29; bit++)
			if (!(x & (1ll << bit)) && (r & (1ll << bit))) {
				stop = true;
				break;
			}
		if (!stop)
			arr.push_back(r);
	}

	if (arr.size() == n - 1) {
		int OR = n - 1;
		for (int e : arr)
			OR |= e;
		if (OR == x)
			arr.push_back(n - 1);
		else 
			arr.push_back(x);
	} else {
		int left = n - arr.size();
		for (int r = 1; r <= left; r++)
			arr.push_back(x);
	}

	for (int e : arr)
		cout << e << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}