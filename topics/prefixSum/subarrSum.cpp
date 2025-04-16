// https://leetcode.com/problems/subarray-sum-equals-k/description/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        // This map stores the frequency of each prefix sum.
        // We initialize it with {0:1} to handle the case where a subarray
        // starting from index 0 sums up to k.
        unordered_map<int, int> prefixSums = {{0, 1}};

        int count = 0; // To store total number of subarrays that sum to k
        int sum = 0;   // Running sum (prefix sum)

        for (int num : nums)
        {
            sum += num; // Update running prefix sum

            // If (sum - k) has been seen before, it means there's a subarray
            // ending at the current index with sum equal to k.
            // For example, if sum = 7 and k = 3, we check how many times we've seen 4.
            if (prefixSums.count(sum - k))
            {
                count += prefixSums[sum - k]; // Add all such subarrays
            }

            // Add current prefix sum to the map
            prefixSums[sum]++;
        }

        return count;
    }
};
