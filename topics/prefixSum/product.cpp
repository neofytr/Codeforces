// https://leetcode.com/problems/product-of-array-except-self/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int length = nums.size();
        // initialize answer array with all elements as 1
        vector<int> answer(length, 1);

        // compute prefix product for each element
        // answer[i] will hold the product of all elements to the left of i
        for (int index = 1; index < length; index++)
        {
            // multiply the previous prefix product with the previous number
            answer[index] = answer[index - 1] * nums[index - 1];
        }

        // initialize suffix product as 1
        int suffix = 1;

        // traverse from the end to compute suffix products
        for (int index = length - 1; index >= 0; index--)
        {
            // multiply the current value in answer (prefix product)
            // with the suffix product (product of elements to the right)
            answer[index] *= suffix;

            // update suffix product by multiplying with the current number
            suffix *= nums[index];
        }

        // return the final answer array
        return answer;
    }
};
