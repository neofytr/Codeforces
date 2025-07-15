#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int coinChange(const vector<int> &arr, const int target) {
        // the array arr represents coins of different denominations
        // return the least number of coins that is needed to make up the amount target
        // if the target amount cannot be made by using any combination of coins, return -1
        // we assume that we have an infinite supply of each coin denomination

        int n = static_cast<int>(arr.size());
        vector<int> dp((target + 1), target + 1);
        // dp[r] is the fewest number of coins required to make the amount r
        dp[0] = 0; // base case (all coins >= 1)

        // 1st method
        for (long long sum = 1; sum <= target; sum++) {
            for (const int coin: arr) {
                if (sum - coin >= 0) {
                    dp[sum] = min(dp[sum], dp[sum - coin] + 1);
                }
            }
        }

        // return dp[target] == target + 1 ? -1 : dp[target];

        // 2nd method
        for (const int coin: arr) {
            // using this new coin, check if we can make any of the sums using lesser number of coins
            for (int sum = coin; sum <= target; sum++) {
                dp[sum] = min(dp[sum], dp[sum - coin] + 1);
            }
        }

        return dp[target] == target + 1 ? -1 : dp[target];
    }
};
