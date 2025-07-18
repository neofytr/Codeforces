// https://leetcode.com/problems/subsets-ii/description/
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
  private:
    void getSubsets(int index, vector<int> &sub, vector<int> &nums, vector<vector<int>> &ans) {
        int n = (int)nums.size();
        if (index >= n) {
            // we have a subset
            ans.push_back(sub);
            return;
        }

        sub.push_back(nums[index]);
        getSubsets(index + 1, sub, nums, ans);
        sub.pop_back();

        // skip duplicates of the element picked at the current level
        while (index < n - 1 && nums[index] == nums[index + 1])
            index++;

        getSubsets(index + 1, sub, nums, ans);
    }

  public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        // nums may contain duplicates; we want to return all possible subsets
        vector<vector<int>> ans;
        vector<int> sub;
        sort(nums.begin(), nums.end());
        getSubsets(0, sub, nums, ans);
        return ans;
    }
};