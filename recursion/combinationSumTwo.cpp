#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
  private:
    void getCombination(vector<int> &candidates, vector<int> &combination, vector<vector<int>> &ans, int target, int index) {

        if (!target) {
            // if target is 0, current combination is valid
            ans.push_back(combination);
            return;
        }

        if (target < 0) {
            // if target goes below 0, no need to continue
            return;
        }

        if (index >= (int)candidates.size()) {
            // if index goes out of bounds, stop recursion
            return;
        }

        // choose the current element
        combination.push_back(candidates[index]);
        // reduce target and move to the next index (each element used at most once)
        getCombination(candidates, combination, ans, target - candidates[index], index + 1);
        // backtrack: remove the element and try next possibility
        combination.pop_back();

        // skip duplicates to avoid repeated combinations
        while (index < (int)candidates.size() - 1 && candidates[index] == candidates[index + 1])
            index++;

        // do not choose the current element, move to next index
        getCombination(candidates, combination, ans, target, index + 1);
        return;
    }

  public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        // we need to find all unique combinations that sum to target
        // each number can be used at most once
        sort(candidates.begin(), candidates.end());              // sort to group duplicates together
        vector<int> combination;                                 // temporary list to store one combination
        vector<vector<int>> ans;                                 // final answer list of combinations
        getCombination(candidates, combination, ans, target, 0); // start recursion
        return ans;
    }
};
