#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];
	set<int> s;
	for (int r = 0; r <= n; r++) s.insert(r);

	for (int r = 1; r <= n; r++)
		if (s.find(arr[r]) != s.end()) s.erase(arr[r]);

	int mex = *s.begin();
	vector<int> cnt(n + 1, 0);
	for (int r = 1; r <= n; r++)
		cnt[arr[r]]++;

	vector<int> p(n + 1, 0);
	p[0] = cnt[0];
	for (int r = 1; r <= n; r++)
		p[r] = p[r - 1] + cnt[r];

	vector<int> k(n + 2, 0);
	for (int r = 0; r <= mex; r++) {
		int left = cnt[r];
		int right = min(n, p[n] - r) + 1;
		k[left] += 1;
		if (right <= n + 1) k[right] -= 1;
	}

	for (int r = 1; r <= n; r++)
		k[r] += k[r - 1];

	for (int r = 0; r <= n; r++)
		cout << k[r] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}