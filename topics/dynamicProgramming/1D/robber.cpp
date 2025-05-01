#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int loot(const vector<int> &arr, const int index, vector<int> &dp) {
        // this returns the maximum loot we can get starting from the house at position index
        if (index >= arr.size()) {
            return 0;
        }

        if (dp[index] != -1) {
            return dp[index];
        }

        const int take = arr[index] + loot(arr, index + 2, dp);
        const int skip = loot(arr, index + 1, dp);

        return dp[index] = max(take, skip);
    }

    static int rob(const vector<int> &arr) {
        const int n = static_cast<int>(arr.size());
        vector<int> dp(n, -1); // dp[i] stores the maximum loot we can get starting from the house at index i
        int maxLootMemo = loot(arr, 0, dp);

        // now for the tabulated solution
        if (n == 1) {
            return arr[0];
        }

        vector<int> tab(n); // tab[i] stores the max loot we can get until index i
        tab[0] = arr[0];
        tab[1] = max(arr[0], arr[1]);

        for (int index = 2; index < n; index++) {
            // max loot until position index is maximum of
            // max loot until position index - 2 + arr[index] (if we're choosing current index to loot, we need to add 2 indexes before)
            // and max loot until position index - 1 (if we're choosing to skip the current index, we need to max loot until the prev position)
            dp[index] = max(dp[index - 2] + arr[index], dp[index - 1]);
        }

        int maxLootTab = dp[n - 1];

        // now for space optimized
        if (n == 1) {
            return arr[0];
        }

        int prev = 0;
        int prev_prev = 0;
        for (int val: arr) {
            int curr = max(prev, prev_prev + val);
            prev_prev = prev;
            prev = curr;
        }

        return prev;
    }
};
