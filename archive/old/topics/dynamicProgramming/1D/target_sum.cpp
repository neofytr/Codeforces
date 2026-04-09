#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int findTargetSumWays(const vector<int> &arr, const int target) {
        const int n = static_cast<int>(arr.size());

        // all elements of arr are positive
        // we want to divide arr into two subsets sub1 and sub2 such that
        // sum(sub1) - sum(sub2) = target
        // also,
        // sum(sub1) + sum(sub2) = sum(arr)
        // so sum(sub1) = (target + sum(arr)) / 2
        // we want to find the number of unordered pairs (sub1, sub2)
        // for every ord pair solution (sub1, sub2), there is a different ord pair (sub2, sub1) which is a solution (if target != 0)
        // so first we count the num of ord pair solutions (sub1, sub2) for target != 0
        // this will be the number of ways we can find a subset sub such that sum(sub) = (target + sum(arr)) / 2
        // we then return half this count as answer — but actually this transformation gives us correct count directly

        const int sum = accumulate(arr.begin(), arr.end(), 0);

        if (target > sum || (sum + target) < 0 || (sum + target) & 1) {
            // either target is too large, or (target + sum) is odd (so can't divide the array like that)
            return 0;
        }

        const int find = (sum + target) / 2;

        // now, we find the number of subsets of arr that sum to 'find'
        // we define dp[index][sum] = number of subsets from [0..index] that sum to 'sum'
        vector<vector<int> > dp(n, vector<int>(find + 1, 0));

        // base cases:
        // we can always make sum = 0 using empty subset
        // if arr[0] == 0, then there are two ways: include it or not => two subsets sum to 0
        // else, only one subset (empty) makes sum = 0
        dp[0][0] = (arr[0] == 0 ? 2 : 1);

        // if arr[0] is <= find, we can include it to make that sum
        if (arr[0] != 0 && arr[0] <= find) {
            dp[0][arr[0]] = 1;
        }

        for (int index = 1; index < n; index++) {
            for (int amount = 0; amount <= find; amount++) {
                // we can exclude arr[index] — keep the same sum
                dp[index][amount] = dp[index - 1][amount];

                // or we can include arr[index], if amount - arr[index] >= 0
                if (amount >= arr[index]) {
                    dp[index][amount] += dp[index - 1][amount - arr[index]];
                }
            }
        }

        // we return the number of subsets that sum to 'find'
        return dp[n - 1][find];
    }
};
