#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool can(vector<int> &nums, int k, int x) {
        // can the maximum amt of money stolen be <= x
        // in other words, can all the money stolen be <= x

        vector<int> choices;
        for (int r = 0; r < nums.size(); r++)
            if (nums[r] <= x)
                choices.push_back(r);

        int last = -2;
        int cnt = 0;
        for (int c : choices)
            if (last + 1 != c)
                last = c, cnt++;

        return cnt >= k;
    } 
public:
    int minCapability(vector<int>& nums, int k) {
        int left = 0;
        int right = 1e9 + 1;

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (can(nums, k, mid))
                right = mid;
            else 
                left = mid;
        }

        return right;
    }
};