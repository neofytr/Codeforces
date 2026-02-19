#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	int N = 0, S = 0, E = 0, W = 0;

	string s; cin >> s;
	for (char c : s)
		if (c == 'N') N++;
		else if (c == 'S') S++;
		else if (c == 'E') E++;
		else W++;

	if (((abs(E - W)) & 1) || ((abs(N - S)) & 1)) {
		cout << "NO" << endl;
		return;
	}

	int x = abs(E - W) >> 1;
	int y = abs(N - S) >> 1;

	if (!x && !y) {

	}

	int na = 0, nb = 0, sa = 0, sb = 0;
	for (; na <= N; na++) {
		sa = na - y;
		if (sa >= 0)
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}