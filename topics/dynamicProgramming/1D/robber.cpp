#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int loot(const vector<int> &arr, const int index, vector<int> &dp) {
        // returns the maximum loot obtainable starting from position index
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
        vector<int> dp(n, -1); // dp[r] stores the maximum loot we can get starting from the house at index r

        return loot(arr, 0, dp);
    }
};
