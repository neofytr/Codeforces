#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int findPeakElement(const vector<int> &arr) {
        // arr doesn't have two consecutive elements equal
        // we can prove that any array having at least one element always has a peak element

        // we maintain the invariant that [left, right] has a peak of the array arr
        int left = 0;
        int right = static_cast<int>(arr.size()) - 1;

        while (left <= right) {
            const int mid = left + (right - left) / 2;

            // if mid is peak, we return it
            if ((mid == 0 || arr[mid] > arr[mid - 1]) && (mid == arr.size() - 1 || arr[mid] > arr[mid + 1])) {
                return mid;
            }

            if (mid > 0 && arr[mid] < arr[mid - 1]) {
                // the left side is non-empty
                // to ensure that every peak of [left, mid - 1] is a peak of arr too, we maintain arr[mid] < arr[mid - 1]
                right = mid - 1;
            } else {
                // now either mid == 0 or arr[mid] > arr[mid - 1] but not both
                // if (mid == 0), then arr[0] < arr[1], or otherwise we would just break off at the first check
                // in this case, the peak is to the right (which isn't empty otherwise we would've broken off at the first check), since the whole array must have a peak

                // if arr[mid] > arr[mid - 1], then we can't be sure every peak of the left side would be a peak of arr
                // also, there is at least one element to the right of mid (or we would've broken off in this case)
                // it also follows then that arr[mid] < arr[mid + 1]
                // so every peak of the subarray [mid + 1, right] is also a peak of the original array
                left = mid + 1;
            }
        }

        return 0;
    }
};
