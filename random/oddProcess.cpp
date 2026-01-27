#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	int v;
	vector<int> odd, even;
	for (int r = 1; r <= n; r++) {
		cin >> v;
		if (v & 1) odd.push_back(v);
		else even.push_back(v);
	}

	sort(odd.begin(), odd.end(), greater<int>());
	sort(even.begin(), even.end(), greater<int>());

	int sz = even.size();
	vector<int> p(sz + 1, 0);
	for (int r = 1; r <= sz; r++)
		p[r] += p[r - 1] + even[r - 1];

	if (odd.empty()) {
		for (int k = 1; k <= n; k++)
			cout << 0 << " ";
		cout << endl;
		return;
	}

	if (even.empty()) {
		for (int k = 1; k <= n; k++)
			if (k & 1) cout << odd[0] << " ";
			else cout << 0 << " ";
		cout << endl;
		return;
	}

	int m = sz + 1;
	for (int k = 1; k <= n; k++) 
		if (k <= m) 
			cout << odd[0] + p[k - 1] << " ";
		else {
			int extra = k - m;
			if (!(extra & 1))
				cout << odd[0] + p[sz] << " ";
			else {
				if (extra + 1 >= odd.size())
					cout << 0 << " ";
				else 
					cout << odd[0] + p[sz - 1] << " ";
			} 
		}
	cout << endl;
}

int32_t main() {
	int t; 
	cin >> t;
	while (t--)
	 	solve();
	return 0;
}