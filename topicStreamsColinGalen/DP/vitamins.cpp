#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define INF (1e10)

int getMask(string &f) {
	int m = 0;
	if (f.find('A') != string::npos) m |= 1;
	if (f.find('B') != string::npos) m |= 2;
	if (f.find('C') != string::npos) m |= 4;
	return m;
}

int32_t main() {
	int n;
	cin >> n;

	vector<int> dp(8, INF);

	dp[0] = 0; // i have only nothing initially
	int c; string f;
	for (int r = 1; r <= n; r++) {
		cin >> c >> f;

		int mask = getMask(f);
		vector<int> newdp = dp;
		for (int m = 0; m <= 7; m++)
			newdp[m | mask] = min(newdp[m | mask], dp[m] + c);
		dp = newdp;
	}

	cout << (dp[7] >= INF ? -1 : dp[7]) << endl;
}
