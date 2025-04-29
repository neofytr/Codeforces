#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * Finds the median of two sorted arrays.
     * Time complexity: O(log(min(m, n))) where m and n are the sizes of nums1 and nums2.
     * Space complexity: O(1)
     */
    static double findMedianSortedArrays(const vector<int> &nums1, const vector<int> &nums2) {
        // ensure nums1 is the smaller array to minimize binary search range
        const vector<int> &A = (nums1.size() <= nums2.size()) ? nums1 : nums2;
        const vector<int> &B = (nums1.size() > nums2.size()) ? nums1 : nums2;

        int m = A.size();
        int n = B.size();

        int totalLeft = (m + n + 1) / 2; // number of elements in the left half of merged array
        int left = 0, right = m;

        while (left <= right) {
            int i = left + (right - left) / 2; // partition A
            int j = totalLeft - i; // partition B

            // elements to the left and right of partition
            int Aleft = (i == 0) ? INT_MIN : A[i - 1]; // largest element from A in the left
            int Aright = (i == m) ? INT_MAX : A[i]; // smallest element from A in the right
            int Bleft = (j == 0) ? INT_MIN : B[j - 1]; // largest element from B in the left
            int Bright = (j == n) ? INT_MAX : B[j]; // smallest element from B in the right

            // binary search invariant:
            // we adjust i such that Aleft <= Bright and Bleft <= Aright
            if (Aleft <= Bright && Bleft <= Aright) {
                // found the correct partition
                if ((m + n) % 2 == 1) {
                    return max(Aleft, Bleft); // odd length, max of left half
                } else {
                    return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0; // even length, average of middle two
                }
            } else if (Aleft > Bright) {
                // we have taken too many elements from A, any number >= 'i' wouldn't work too
                // so reduce the right half of search space
                right = i - 1; // move left in A
            } else if (Bleft > Aright) {
                // we have taken too less from A
                // any number <= 'i won't work too
                // so reduce the left half of search space
                left = i + 1; // move right in A
            }
        }

        throw runtime_error("Input arrays are not sorted or invalid.");
    }
};
