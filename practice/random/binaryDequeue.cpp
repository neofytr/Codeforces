#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, s; cin >> n >> s;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	vector<int> pref(n + 1, 0), suff(n + 2, 0);
	for (int i = 1;  i <= n; i++)
		pref[i] += pref[i - 1] + arr[i];
	for (int i = n; i >= 1; i--)
		suff[i] += suff[i + 1] + arr[i];

	vector<int> p = pref, sf = suff;
	sort(p.begin(), p.end()), sort(sf.begin(), sf.end() - 1);
	for (int i = 0; i <= n; i++) {
		int target = s - p[i];
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}