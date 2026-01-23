#include <bits/stdc++.h>
using namespace std;

#define int long long

int calc(int x) {
	int ones = x % 10;
	int twos = ((x % 100) - ones) / 10;

	switch (ones) {
	case 1:
	case 2:
	case 4:
	case 8:
		return (twos & 1);

	case 3:
	case 6:
	case 7:
	case 9:
		return !(twos & 1);
	}

	return 0;
}

void solve(int t) {
	int n;
	cin >> n;

	if (n == 1) {
		cin >> n;
		cout << "YES" << endl;
		return;
	}

	int v;
	set<int> s;
	for (int r = 1; r <= n; r++)
		cin >> v, s.insert(v);

	bool found = false;
	int alpha = -1;
	for (int e : s) {
		if (!found && !(e % 10)) found = true, alpha = e;
		else if (found && !(e % 10)) {
			cout << "NO" << endl;
			return;
		}
	}

	if (found) {
		// we have exactly one remainder 0
		// find if we have any remainder 5

		for (int e : s)
			if (e % 10 == 5) 
				if (e + 5 != alpha) {
					cout << "NO\n";
					return;
				}
		
		// we have remainder 0, some remainder 5 (which can be conv to the remainder 0 one)
		// if we have some other remainder, we are doomed

		for (int e : s)
			if ((e % 10) != 5 && (e % 10) != 0) {
				cout << "NO" << endl;
				return;
			}

		cout << "YES" << endl;
		return;
	}


	// no remainder 0 from here
	for (int e : s)
		if (e % 10 == 5) {
			for (int g : s)
				if (g != e) {
					cout << "NO" << endl;
					return;
				}

			cout << "YES" << endl;
			return;
		}

	// no remainder 0 and 5 from here
	int a1 = *s.begin();
	for (int e : s)
		if (calc(e) != calc(a1)) {
			cout << "NO" << endl;
			return;
		}

	cout << "YES" << endl;
}

int32_t main() {
	int t;
	cin >> t;

	for (int r = 1; r <= t; r++) {
		solve(r);
	}
	return 0;
}