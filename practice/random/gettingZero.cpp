#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1LL << 15)

int32_t main() {
	int n;
	cin >> n;

	int val;
	int timer = 1;
	for (int r = 1; r <= n; r++) {
		cin >> val;

		// We can reduce val to zero in 15 operations
		// Can we do it in less than or equal to 14 operations?

		// It is not optimal to do a +1 operation after a *2 operation
		// So, first we do any number of +1 operations we want, and then
		// all the *2 operations we want

		if (!val) {
			cout << 0 << endl;
			continue;
		}

		int res = 15;
		for (int op = 0; op <= 14; op++) {
			int x = val + op;
			res = min(res, op + (15 - __builtin_ctzll(x)));
		}

		cout << res << " ";
	}
	cout << endl;
	return 0;
}