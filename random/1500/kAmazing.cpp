#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(3 * 1e5)

int a[MAX + 1];

struct cmp {
	bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
		if (a.first < b.first) return true;
		if (a.first == b.first && a.second < b.second) return true;
		return false;
	}
};

void solve() {
	int n; cin >> n;
	for (int r = 1; r <= n; r++) cin >> a[r];

	vector<int> f(n + 1, 0);
	set<pair<int, int>, cmp> s;

	for (int k = 1; k <= n; k++) {
		for (int j = k; j <= n; j += k) {
			f[a[j]]++;
			s.insert({f[a[j]], a[j]});
		}

		auto itr = s.lower_bound({n - k + 1, 0});
		cout << itr->second << " ";
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}