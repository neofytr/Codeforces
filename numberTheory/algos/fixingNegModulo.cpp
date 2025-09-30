#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int q;
	cin >> q;
	while(q--) {
		int a, b;
		cin >> a >> b;

		// 1 <= a, b <= 1e9
		int r = (a - b) % MOD;
		if (r < 0) r += MOD; // a very efficient way to handle negative remainders
		cout << r;
	}
}