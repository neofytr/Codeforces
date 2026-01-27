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
}

int32_t main() {
	int t; cin >> t;

	while (t--) solve;
	return 0;
}