#include <bits/stdc++.h>
using namespace std;

#define int long long

int cnt(int r, int n, string &str, vector<int> &dp, vector<vector<int>> &f) {
	if (r >= n)
		return 0;
	if (dp[r] != -1)
		return dp[r];

	// either i can delete the current character
	int res = 1 + cnt(r + 1, n, str, dp, f);

	// or make the current pair (if possible)
	vector<int> &vec = f[str[r] - 'a'];
	auto itr = upper_bound(vec.begin(), vec.end(), r);
	if (itr == vec.end())
		return dp[r] = res;
	res = min(res, (*itr - 1) - (r + 1) + 1 + cnt(*itr + 1, n, str, dp, f));
	return dp[r] = res;
}

void greedy() {
	string str;
	cin >> str;

	int res = 0;
	int n = (int)str.length();
	int cnt[26];

	memset((void *)cnt, 0, sizeof(cnt));
	for (int r = 0; r < n; r++) {
		if (cnt[str[r] - 'a']) 
			res += 2, memset((void *)cnt, 0, sizeof(cnt));
		else
			cnt[str[r] - 'a']++;
	}

	cout << n - res << endl;
}

void solve() {
    string str;
    cin >> str;

    int n = str.length();

    // f[c] = all indices where char c appears
    vector<vector<int>> f(26);
    for (int i = 0; i < n; i++)
        f[str[i] - 'a'].push_back(i);

    // dp[r] is the minimum number of characters that must be
    // removed to make [r, n - 1] even
    vector<int> dp(n, -1);
    cnt(0, n, str, dp, f);

    cout << dp[0] << endl;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) greedy();
    return 0;
}
