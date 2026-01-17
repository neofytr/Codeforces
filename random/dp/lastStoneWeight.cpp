#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
    	int n = stones.size();

    	vector<int> arr(n + 1);
    	for (int r = 1; r <= n; r++) arr[r] = stones[r - 1];

    	vector<unordered_map<int, bool>> dp(n + 1);

    	dp[0][0] = true;
    	for (int r = 1; r <= n; r++)
    		for (int x = -3000; x <= 3000; x++)
    			if (dp[r - 1][x]) dp[r][x + stones[r]] = dp[r][x - stones[r]] = true;

    	for (int x = 0; x <= 3000; x++)
    		if (dp[n][x])
    			return x;
    }
};