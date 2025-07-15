#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int rob(const vector<int> &arr) {
        const int n = static_cast<int>(arr.size());

        // we can either loot the last or loot the first one, but never both together

        // can't loot the last one
        vector<int> dp(n); // dp[i] stores the max loot until index i
        if (n == 1) {
            return arr[0];
        }
        if (n == 2) {
            return max(arr[0], arr[1]);
        }
        dp[0] = arr[0];
        dp[1] = max(arr[0], arr[1]);

        for (int index = 2; index < n - 1; index++) {
            // either we would take this index or not
            // if we take this index, the max would be current index + max of position index - 2
            // if we don't, the max would be max of position index - 1
            // dp[index] would be the max of these two maxes
            dp[index] = max(arr[index] + dp[index - 2], dp[index - 1]);
        }

        const int first = dp[n - 2];
        dp.clear();

        // can't loot the first one

        dp[1] = arr[1];
        dp[2] = max(arr[1], arr[2]);
        for (int index = 3; index < n; index++) {
            dp[index] = max(arr[index] + dp[index - 2], dp[index - 1]);
        }

        const int second = dp[n - 1];

        return max(first, second);
    }
};
