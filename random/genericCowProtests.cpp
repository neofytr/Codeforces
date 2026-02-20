#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1e9 + 9)

int32_t main() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<int> dp(n + 1);
	if (arr[1] >= 0) dp[1] = 1;
	else dp[1] = 0;
}