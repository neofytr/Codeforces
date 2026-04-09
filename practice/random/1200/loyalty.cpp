#include <bits/stdc++.h>
using namespace std;

#define int long long 

// (s + a) / x > s / x
// 
// (s / x + a / x) > s / x
// (r + a) / x > (r / x)
// 
// for this to be true, its necessary and sufficient that
// r + a >= x
// a >= x - r
// 
// 0 <= r < x
// 1 <= a <= x


void solve() {
	int n, x;
	cin >> n >> x;

	int val;
	multiset<int> prices;
	for (int r = 1; r <= n; r++) cin >> val, prices.insert(val);

	int sum = 0, pts = 0;
	vector<int> list;
	while (!prices.empty()) {
		int r = sum % x;
		int maxi = *prices.rbegin();
		int mini = *prices.begin();
		if (maxi < x - r)
			sum += mini, prices.erase(prices.begin()), list.push_back(mini);
		else 
			sum += maxi, prices.erase(--prices.end()), pts += maxi, list.push_back(maxi);
	}		

	cout << pts << endl;
	for (int v : list)
		cout << v << " ";
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