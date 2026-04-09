#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	string str;
	cin >> str;

	vector<int> pa(n + 1, 0), pb(n + 1, 0);
	for (int r = 1; r <= n; r++) {
		pa[r] += pa[r - 1] + (str[r - 1] == 'a' ? 1 : 0);
		pb[r] += pb[r - 1] + (str[r - 1] == 'b' ? 1 : 0);
	}

	if (!pa[n] || !pb[n]) {
		cout << -1 << endl;
		return;
	}

	if (pa[n] == pb[n]) {
		cout << 0 << endl;
		return;
	}

	// If we remove arr[l, r], then,
	// pa[n] - (pa[r + 1] - pa[l]) = pb[n] - (pb[r + 1] - pb[l])
	// pa[n] - pb[n] = (pa[r + 1] - pb[r + 1]) - (pa[l] - pb[l])
	// q[n] = q[r + 1] - q[l]
	// q[l] = q[r + 1] - q[n]

	vector<int> q(n + 1, 0);
	for (int r = 0; r <= n; r++) q[r] = pa[r] - pb[r];

	unordered_map<int, vector<int>> mp;
	int mini = LLONG_MAX;

	for (int r = 0; r < n; r++) {
		mp[q[r]].push_back(r);
		int target = q[r + 1] - q[n];
		if (!mp[target].empty()) {
			vector<int> &v = mp[target];
			mini = min(mini, r - *v.rbegin() + 1);
		}
	}

	if (mini == n)
		cout << -1 << endl;
	else 
		cout << mini << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}