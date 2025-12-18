#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> next(n + 1);
	vector<int> prev(n + 1);
	vector<int> arr(n + 1);
	set<pair<int, int>> s;
	for (int r = 1; r <= n; r++) {
		cin >> arr[r];
		next[r] = r + 1;
		prev[r] = r - 1;
		if (!prev[r])
			prev[r] = n;
		if (next[r] == n + 1)
			next[r] = 1;
		s.insert({arr[r], r});
	}

	int cost = 0;
	while (s.size() > 1) {
		auto [elt, idx] = *s.begin();
		int nxt = next[idx];
		int prv = prev[idx];

		s.erase(s.begin());
		if (arr[nxt] <= arr[prv])
			cost += arr[nxt], prev[nxt] = prev[idx], next[prv] = next[idx];
		else 
			cost += arr[prv], next[prv] = next[idx], prev[nxt] = prev[idx];
	}

	cout << cost << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
} 