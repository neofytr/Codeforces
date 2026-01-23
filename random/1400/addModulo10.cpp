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
		cout << "YES" << endl;
		return;
	}

	int v;
	set<int> s;
	for (int r = 1; r <= n; r++)
		cin >> v, s.insert(v);

	bool found = false;
	for (int e : s)
		if (!found && !(e % 10)) found = true;
		else if (found && !(e % 10)) {
			cout << "NO" << endl;
			return;
		}

	if (found) {
		
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
	
}

int32_t main() {
	int t;
	cin >> t;

	for (int r = 1; r <= t; r++) {
		solve(r);
	}
	return 0;
}