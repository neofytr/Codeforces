#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string t; cin >> t;

	int n = t.length();
	for (int s = 1; s <= n; s++) {
		int a = 2 * s - n;
		if (a >= 1 && a < n)
			if (t.substr(0, s) == t.substr(s - a, s)) {
				cout << "YES" << endl;
				cout << t.substr(0, s) << endl;
				return 0;
			}
	}

	cout << "NO" << endl;
	return 0;
}