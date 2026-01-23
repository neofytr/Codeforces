#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int t) {
	int n;
	cin >> n;

	if (n == 1) {
		cout << "YES" << endl;
		return;
	}

	int v;
	set<int> s;
	for (int r = 1; r <= n; r++)
		cin >> v, s.insert(v);

	bool found = false;
	int alpha = -1;
	for (int e : s)
		if (!found && !(e % 10)) found = true, alpha = e;
		else if (found && !(e % 10)) {
			cout << "NO" << endl;
			return;
		}

	if (found) {
		s.erase(alpha);
		for (int e : s) {
			int rem = e % 10;
			if (e > alpha || ((alpha - e) % rem)) {
				cout << "NO" << endl;
				return;
			}
	
			int k = ((alpha - e) / rem) + 1;
			if (__builtin_popcountll(k) > 1) {
				cout << "NO" << endl;
				return;
			}
		}
		cout << "YES" << endl;
		return;
	}

	int a1 = *s.begin(), rem1 = a1 % 10;
	int a2 = *(++s.begin()), rem2 = a2 % 10;

	set<int> psbl;
	for (int j1 = 0; j1 <= 21; j1++)
		for (int j2 = 0; j2 <= 21; j2++) 
			if (a2 - a1 + rem2 - rem1 == (1ll << j1) * rem1 - (1ll << j2) * rem2)
				psbl.insert(a1 + ((1ll << j1) - 1) * rem1);

	s.erase(a1);
	s.erase(a2);
}

int32_t main() {
	int t;
	cin >> t;

	for (int r = 1; r <= t; r++) {
		solve(r);
	}
	return 0;
}