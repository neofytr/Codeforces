#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	multiset<int> s;
	vector<int> a(n, 0);
	for (int i = 1; i <= n - 1; i++) cin >> a[i];

	vector<int> miss;
	for (int i = 0; i <= n - 1; i++) s.insert(a[i] - a[i - 1]);
	for (int i = 1; i <= n; i++)
		if (!s.count(i)) miss.push_back(i);

	if (miss.size() > 2) {
		cout << "NO" << endl;
		return;
	}

	if (miss.size() == 1) {
		cout << "YES" << endl;
		return;
	}

	for (int i = 0; i <= n - 2; i++)
		if (a[i + 1] - a[i] == miss[0] + miss[1] && a[i + 1] - a[i] > n) {
			cout << "YES" << endl;
			return;
		} else if (a[i + 1] - a[i] <= n && a[i + 1] - a[i] == miss[0] + miss[1]) {
			int c = a[i + 1] - a[i];
			if (s.count(c) > 1) {
				cout << "YES" << endl;
				return;
			}
		}

	cout << "NO" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}