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

	int x = (E - W) / 2;
	int y = (N - S) / 2;

	if (!x && !y) {
		int na, sa, ea, wa;

		if (N && W) {
			na = N, sa = S;
			ea = 0, wa = 0;
		} else if (!N && W) {
			na = 0, sa = 0;
			ea = E / 2, wa = W / 2;

			int eb = E - ea, wb = W - wa;
			if (!(ea + wa) || !(wb + eb)) {
				cout << "NO" << endl;
				return;
			}
		} else if (N && !W) {
			na = N / 2, sa = S / 2;
			ea = wa = 0;

			int nb = N - na, sb = S - sa;
			if (!(nb + sb) || !(na + sa)) {
				cout << "NO" << endl;
				return;
			}
		}

		for (int c : s)
		if (c == 'N') {
			if (na) cout << "R", na--;
			else cout << "H";
		} else if (c == 'E') {
			if (ea) cout << "R", ea--;
			else cout << "H";
		} else if (c == 'S') {
			if (sa) cout << "R", sa--;
			else cout << "H";
		} else {
			if (wa) cout << "R", wa--;
			else cout << "H";
		}
	cout << endl;
	return;
	}

	int na, sa;
	for (na = 0; na <= N; na++) {
		sa = na - y;
		if (sa >= 0 && sa <= S && (2 * (na - sa) == N - S)) {
			break;
		}
	}

	int ea, wa;
	for (ea = 0; ea <= E; ea++) {
		wa = ea - x;
		if (wa >= 0 && wa <= W && (2 * (ea - wa) == E - W)) 
			break;
	}

	for (int c : s)
		if (c == 'N') {
			if (na) cout << "R", na--;
			else cout << "H";
		} else if (c == 'E') {
			if (ea) cout << "R", ea--;
			else cout << "H";
		} else if (c == 'S') {
			if (sa) cout << "R", sa--;
			else cout << "H";
		} else {
			if (wa) cout << "R", wa--;
			else cout << "H";
		}
	cout << endl;
	
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}