#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int> &nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            }

            if (nums[mid] >= nums[left]) {
                // the subarray [left, mid] is sorted
                if (target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            if (nums[mid] <= nums[right]) {
                // the subarray [mid, right] is sorted
                if (target > nums[mid]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};
