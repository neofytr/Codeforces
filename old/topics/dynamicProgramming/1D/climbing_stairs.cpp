#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int climbStairs(const int n) {
        if (n == 1) {
            return 1;
        }

        vector<int> dp(n + 1, 0);
        // each time we can climb either 1 or 2 steps
        // base cases
        dp[1] = 1;
        dp[2] = 2; // 1-1 or 2
        for (int index = 3; index <= n; index++) {
            // the number of ways to reach
            // stair index is the number of ways to reach
            // stair index - 1(then take a 1 step) or reach
            // stair index - 2 (then take a 2-step)
            dp[index] = dp[index - 1] + dp[index - 2];
        }

        return dp[n];
    }
};
