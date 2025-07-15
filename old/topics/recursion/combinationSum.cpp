#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void getCombinations(const vector<int> &candidates, vector<int> &current,
                         vector<vector<int>> &answer, int remaining, int index)
    {
        if (!remaining)
        {
            answer.push_back(current);
            return;
        }

        if (remaining < 0 || index >= candidates.size())
        {
            return;
        }

        current.push_back(candidates[index]);
        getCombinations(candidates, current, answer, remaining - candidates[index], index);
        current.pop_back();

        getCombinations(candidates, current, answer, remaining, index + 1);
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> answer;
        vector<int> current;
        current.reserve(target);
        getCombinations(candidates, current, answer, target, 0);
        return answer;
    }
};
