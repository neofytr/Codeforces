#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> ans;

        // nums is sorted in non-decreasing order
        // we maintain the invariant
        // arr[left] < target
        // arr[right] >= target

        int left = -1;
        int right = nums.size();
        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid;
            } else {
                left = mid;
            }
        }

        if (right < nums.size() && nums[right] == target) {
            ans.push_back(right);
            int final = right;
            right++;
            while (right < nums.size() && nums[right] == target) {
                final++;
                right++;
            }

            ans.push_back(final);
        } else {
            ans.push_back(-1);
            ans.push_back(-1);
        }

        return ans;
    }
};
