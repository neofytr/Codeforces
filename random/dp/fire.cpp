#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(1e2)
#define TMAX (int)(20 * 100)

int t[MAX + 1], b[MAX + 1], v[MAX + 1];
int dp[MAX + 1][TMAX + 1];
pair<int, int> vec[MAX + 1];
int32_t main() {
	int n;
	cin >> n;

	for (int r = 1; r <= n; r++)
		cin >> t[r] >> b[r] >> v[r];

	int sz = 0;
	for (int r = 1; r <= n; r++)
		if (b[r] >= t[r]) vec[++sz] = {b[r], r};

	if (!sz) {
		cout << 0 << endl;
		cout << 0 << endl;
		return 0;
	}
	sort(vec + 1, vec + sz + 1);

	// dp[i][j] is the maximum value we can get out of the saved items in vec[1, i]
	// with total time spent = j

	for (int i = 0; i <= sz; i++)
	for (int j = 0; j <= TMAX; j++)
		dp[i][j] = -1e15;

	dp[0][0] = 0;
	for (int i = 1; i <= sz; i++) {
		int idx = vec[i].second;

		for (int j = 0; j <= TMAX; j++)
			dp[i][j] = dp[i - 1][j];

		for (int j = t[idx]; j < b[idx]; j++) {
			if (dp[i - 1][j - t[idx]] >= 0)
				dp[i][j] = max(dp[i][j], dp[i - 1][j - t[idx]] + v[idx]);
		}
	}

	int maxi = LLONG_MIN, time = -1;
	for (int j = 0; j <= TMAX; j++) {
		if (dp[sz][j] > maxi) time = j, maxi = dp[sz][j];
	}
	cout << maxi << endl;

	vector<int> s;
	int r = sz;
	while (r >= 1) {
		int idx = vec[r].second;
		if (time >= t[idx] && time < b[idx] && dp[r][time] == dp[r - 1][time - t[idx]] + v[idx])
			s.push_back(idx), r--, time -= t[idx];
		else r--;
	}

	cout << s.size() << endl;
	reverse(s.begin(), s.end());
	for (int e : s)
		cout << e << " ";
	cout << endl;
	return 0;
}