#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> canPartition(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr(n + 1);

        int sum = 0;
        for (int r = 1; r <= n; r++) arr[r] = nums[r - 1], sum += arr[r];

        if (sum & 1) return {};

    	vector<bool> dp(sum + 1);
    	dp[0] = true;

    	// can[r][x] is true if some subset of arr[1, r] sums to x
    	for (int r = 1; r <= n; r++)
    		for (int x = sum; x >= arr[r]; x--)
    			dp[x] = dp[x] | dp[x - arr[r]];

    	if (!dp[sum >> 1]) return {};

    	vector<int> part;

    	int x = sum >> 1;
    	while (x) {
    		for (int r = 1; r <= n; r++)
    			if (sum >= arr[r] && dp[sum - arr[r]]) {
    				part.push_back(r);
    				sum -= arr[r];
    				break;
    			}
    	}
    	return part;
    }
};