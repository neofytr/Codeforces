#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	string str;
	cin >> str;

	int wcnt = 0;
	for (char c : str)
		if (c == 'W')
			wcnt++;
	int bcnt = n - wcnt;

	if (!bcnt || !wcnt) {
		cout << 0 << endl;
		return 0;
	}

	// WW <-> BB
	// BW <-> WB
	// In one operation, wcnt (bcnt) increases by 2, decreases by 2, or stays the same
	// Thus, after any number of operations, the parity of wcnt (bcnt) remains the same

	// Thus, if initially both bcnt and wcnt are odd, neither of them can become 0 (even),
	// which is necessary for all the balls to be the same color
	if ((bcnt & 1) && (wcnt & 1)) {
		cout << -1 << endl;
		return 0;
	}

	// If initially, one is even and one is odd, we cannot take the odd one to 0
	// Thus, we are constrained to take the even one to 0

	vector<int> res;
	if (!(bcnt & 1) && (wcnt & 1)) {
		int r = 0;
		// We convert the first n - 1 balls to W
		// The last ball will automatically be W
		// This is true since if the last ball is B, then bcnt = 1 at that
		// point, which is odd, which is impossible since bcnt was even
		// at the beginning
		while (r < n - 1) {
			if (str[r] == 'B' && str[r + 1] == 'B') {
				str[r] = 'W', str[r + 1] = 'W';
				res.push_back(r + 1), r += 2;
			} else if (str[r] == 'W' && str[r + 1] == 'B') {
				r++;
			} else if (str[r] == 'B' && str[r + 1] == 'W') {
				str[r] = 'W', str[r + 1] = 'B';
				res.push_back(r + 1), r++;
			} else {
				r += 2;
			}
		}
	} else {
		int r = 0;
		while (r < n - 1) {
			if (str[r] == 'W' && str[r + 1] == 'W') {
				str[r] = 'B', str[r + 1] = 'B';
				res.push_back(r + 1), r += 2;
			} else if (str[r] == 'B' && str[r + 1] == 'W') {
				r++;
			} else if (str[r] == 'W' && str[r + 1] == 'B') {
				str[r] = 'B', str[r + 1] = 'W';
				res.push_back(r + 1), r++;
			} else {
				r += 2;
			}
		}
	}

	cout << res.size() << endl;
		for (int idx : res)
			cout << idx << " ";
		cout << endl;
}
