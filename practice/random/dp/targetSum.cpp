#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> arr(n + 1);

        int total = 0;
        for (int r = 1; r <= n; r++) arr[r] = nums[r - 1], total += arr[r];
        total += target;

    	if (total & 1) return 0;
    	total >>= 1;

    	unordered_map<int, int> dp;
    	dp[0] = 1;

    	for (int r = 1; r <= n; r++)
    		for (int x = total; x >= arr[r]; x--)
    			dp[x] += dp[x - arr[r]];

    	return dp[total];
    }
};