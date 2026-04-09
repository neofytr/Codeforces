#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	int val;
	list<int> lst;
	for (int r = 1; r <= n; r++)
		cin >> val, lst.push_back(val);

	int largest = n;
	while (true) {
		if (*lst.begin() == largest) {
			cout << "NO\n";
			return;
		}

		if (*lst.rbegin() == largest) {
			cout << "YES\n";
			return;
		}

		largest--;
 	}
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}