#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(1e5)

int32_t main() {
	int n, k;
	cin >> n >> k;

	string s; cin >> s;
	vector<int> str(n + 1);
	for (int r = 1; r <= n; r++)
		str[r] = s[r - 1] - 'a';

	// dp[r] is the maximum length of substring consisting of
	// equal characters that we can achieve till now if we change
	// r characters



	return 0;
}