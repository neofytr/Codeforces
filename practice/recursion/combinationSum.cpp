#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
  private:
    void getMultiset(vector<int> &candidates, vector<int> &multiSet, vector<vector<int>> &ans, int target, int index) {
        if (!target) {
            ans.push_back(multiSet);
            return;
        }
        if (target < 0)
            return;
        if (index >= (int)candidates.size())
            return;

        // either we choose the current element in the multiSet (again), or we don't
        multiSet.push_back(candidates[index]);
        getMultiset(candidates, multiSet, ans, target - candidates[index], index);
        multiSet.pop_back();
        getMultiset(candidates, multiSet, ans, target, index + 1);
        return;
    }

    void getMultisetTwo(vector<int> &candidates, vector<int> &multiSet, vector<vector<int>> &ans, int target, int index) {
        if (!target) {
            ans.push_back(multiSet);
            return;
        }
        if (target < 0)
            return;
        if (index >= (int)candidates.size())
            return;

        int initTarget = target;
        int counter = 0;
        while (target > 0) {
            target -= candidates[index];
            multiSet.push_back(candidates[index]);
            getMultisetTwo(candidates, multiSet, ans, target, index + 1);
            counter++;
        }

        while (counter--) {
            multiSet.pop_back();
        }
        getMultisetTwo(candidates, multiSet, ans, initTarget, index + 1);
    }

  public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        // candidates is an array of distinct, positive integers
        // we want to return all multi-sets of the array candidates whose element-sum is target
        vector<vector<int>> ans;
        vector<int> multiset;
        getMultisetTwo(candidates, multiset, ans, target, 0);
        return ans;
    }
};