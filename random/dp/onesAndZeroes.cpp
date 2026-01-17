#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int sz = strs.size();

        vector<int> one(sz + 1, 0), zero(sz + 1, 0);
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));

     	for (int r = 1; r <= sz; r++) {
     		string &str = strs[r - 1];
     		one[r] = count(str.begin(), str.end(), '1');
     		zero[r] = count(str.begin(), str.end(), '0');
     	}

     	dp[0][0] = 0;
     	for (int r = 1; r <= sz; r++) {
     		int o = one[r], z = zero[r];

     		for (int i = n; i >= o; i--)
     			for (int j = m; j >= z; j--)
     				dp[i][j] = max(dp[i][j], dp[i - o][j - z] + 1);
     	}	

     	int maxi = LLONG_MIN;
     	for (int i = 0; i <= n; i++)
     		for (int j = 0; j <= m; j++)
     			maxi = max(maxi, dp[i][j]);
     	return maxi;
    }
};