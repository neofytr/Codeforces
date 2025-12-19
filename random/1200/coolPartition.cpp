#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	set<int> tot;
	vector<int> arr(n + 1), f(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r], f[arr[r]]++, tot.insert(arr[r]);

	int r = n;
	int cnt = 0;
	while (r >= 1) {
		set<int> s;
		vector<int> v;
		while (r >= 1 && s.size() < tot.size()) {
			if (!(--f[arr[r]]))
				v.push_back(r);
			s.insert(arr[r]), r--;
		}

		for (int e : v)
			tot.erase(arr[e]);
		cnt++;
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}