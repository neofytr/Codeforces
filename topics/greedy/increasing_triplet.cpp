// https://leetcode.com/problems/increasing-triplet-subsequence/description/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // this function checks whether there exists an increasing triplet subsequence
    // in the given vector `nums`. An increasing triplet means there are indices
    // i < j < k such that nums[i] < nums[j] < nums[k].
    bool increasingTriplet(vector<int> &nums)
    {
        // initialize the smallest and second smallest numbers seen so far
        int first = INT_MAX;
        int second = INT_MAX;

        for (int index = 0; index < nums.size(); index++)
        {
            // the if-else structure always ensures that second comes
            // after first in array, and the last comes after second

            if (nums[index] <= first)
            {
                // update `first` if current number is smaller than or equal to `first`
                first = nums[index];
            }
            else if (nums[index] <= second)
            {
                // update `second` if current number is greater than `first`
                // but smaller than or equal to `second`
                second = nums[index];
            }
            else
            {
                // if current number is greater than both `first` and `second`,
                // then an increasing triplet has been found
                return true;
            }
        }

        // if no such triplet is found, return false
        return false;
    }
};
