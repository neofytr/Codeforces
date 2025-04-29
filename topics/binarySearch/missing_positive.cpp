#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int findKthPositive(const vector<int> &arr, const int k) {
        int num = 0; // count of number of missing positive integers
        int curr = 1; // the current number we're checking

        while (true) {
            if (!binary_search(arr.begin(), arr.end(), curr)) {
                // the current number isn't in the array
                num++;
                if (num == k) {
                    break;
                }
            }
            curr++;
        }

        return curr;
    }
};
