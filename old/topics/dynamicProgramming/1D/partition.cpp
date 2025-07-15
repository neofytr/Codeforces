#include <bits/stdc++.h>
using namespace std;

/*
 *
#include <bits/stdc++.h>
using namespace std;

#define MAX_TARGET (200 * 100)

class Solution {
public:
    static bool canPartition(const vector<int> &arr) {
        const int total = accumulate(arr.begin(), arr.end(), 0);
        if (total & 1) return false;

        bitset<MAX_TARGET + 1> reachable;
        reachable.set(0);

        for (const int num: arr) {
            reachable |= (reachable << num);
            if (reachable[total / 2]) {
                return true; // early stop
            }
        }

        return false;
    }
};
 */

class Solution {
public:
    static bool canPartition(const vector<int> &arr) {
        const int total = accumulate(arr.begin(), arr.end(), 0);
        if (total & 1) return false;

        const int target = total / 2;
        vector<bool> dp(target + 1, false);
        // dp[r] is true if there is a subset with sum r, 0 <= r <= target; false otherwise
        dp[0] = true; // we can make sum 0 (by not taking anything in the subset)

        for (const int num: arr) {
            // we want to choose an element only once, so we start from the back
            for (int sum = target; sum >= num; sum--) {
                dp[sum] = dp[sum] || dp[sum - num];
            }
        }

        return dp[target];
    }
};
