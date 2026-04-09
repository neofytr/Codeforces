#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	string str;
	cin >> str;

	int n = (int)str.length();

	// if a string is beautiful, then so is any substring of it
	// subsegment monotonic

	// a string is beautiful iff at locations of the same parity, it doesn't have both 1 and 0

	int cnt = 0;
	int l = 0;

	int onesEven = 0;
	int onesOdd = 0;
	int zeroEven = 0;
	int zeroOdd = 0;
	for (int r = 0; r < n; r++) {
		if (str[r] == '1') {
			if (!((r - l) & 1))
				onesEven++;
			else
				onesOdd++;
		} 
		if (str[r] == '0') {
			if (!((r - l) & 1))
				zeroEven++;
			else 
				zeroOdd++;
		}
		while (l <= r && !((!onesEven && !zeroOdd) || (!onesOdd && !zeroEven))) {
			swap(onesEven, onesOdd);
			swap(zeroEven, zeroOdd);
			if (str[l] == '1') 
				onesOdd--;
			if (str[l] == '0')
				zeroOdd--;
			l++;
		}

		if (l <= r)
			cnt += (r - l + 1);
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}

	return 0;
}