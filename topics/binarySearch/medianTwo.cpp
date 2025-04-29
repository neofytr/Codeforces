#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static double findMedianSortedArrays(const vector<int> &nums1, const vector<int> &nums2) {
        // ensure nums1 is the smaller array to minimize binary search range
        const vector<int> &A = (nums1.size() <= nums2.size()) ? nums1 : nums2;
        const vector<int> &B = (nums1.size() > nums2.size()) ? nums1 : nums2;

        const int m = static_cast<int>(A.size());
        const int n = static_cast<int>(B.size());

        // we have m <= n

        // m + n is even
        const int size = (m + n + 1) / 2;
        // number of elements in the left half; for odd the left half includes the median
        // 'size' >= m

        int left = 0, right = m; // the number of elements coming from A in the left half
        // can be from 0 to m

        while (left <= right) {
            const int mid = left + (right - left) / 2;
            const int fromRight = size - mid;

            const int l1 = (mid == 0) ? INT_MIN : A[mid - 1];
            const int r1 = (mid == m) ? INT_MAX : A[mid];
            const int l2 = (fromRight == 0) ? INT_MIN : B[fromRight - 1];
            const int r2 = (fromRight == n) ? INT_MAX : B[fromRight];

            if (l1 <= r2 && l2 <= r1) {
                // we have found the correct distribution
                if ((m + n) & 1) {
                    return max(l1, l2);
                }
                return ((max(l1, l2)) + min(r1, r2)) / 2.0;
            } else if (l1 > r2) {
                // we have taken too many elements from A
                // any mid >= l1 won't work too
                // so reduce the search space to the left half
                right = mid - 1;
            } else if (l2 > r1) {
                // we have taken too many elements from B, that is, too little elements
                // from A
                // any mid <= l1 won't work too
                // so reduce the search space to the right half
                left = mid + 1;
            }
        }


        throw runtime_error("Input arrays are not sorted or invalid.");
    }
};
