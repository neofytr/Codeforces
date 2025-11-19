#include <bits/stdc++.h>
using namespace std;

#define int long long 

// let n is even
// n / 2 < 1
// n < 2
// n = 1

//

void solve() {
	int n;
	cin >> n;

	int res = 0;
	while (n > 0) {
		if (!(n & 1))
			res += (n >>= 1);
		else 
			res += 1, n--;

		if (!(n & 1))
			n >>= 1;
		else 
			n--;
	}

	cout << res << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}