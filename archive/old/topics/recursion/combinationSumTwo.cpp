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

        int length = candidates.size();

        if (remaining < 0 || index >= length)
        {
            return;
        }

        // now we choose which element to pick in this call
        for (int curr_index = index; curr_index < length; curr_index++)
        {
            // skip duplicates at the current level
            if (curr_index > index && candidates[curr_index] == candidates[curr_index - 1])
            {
                continue;
            }

            // first occurence of an element at the current level
            current.push_back(candidates[curr_index]); // pick it
            getCombinations(candidates, current, answer, remaining - candidates[curr_index], curr_index + 1);
            current.pop_back(); // remove it so we can pick a diff one at the current level
        }
    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        vector<vector<int>> answer;
        vector<int> current;
        current.reserve(target);

        sort(candidates.begin(), candidates.end());
        getCombinations(candidates, current, answer, target, 0);
        return answer;
    }
};
