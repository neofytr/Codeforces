#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int findMin(const vector<int> &arr) {
        int left = 0;
        int right = static_cast<int>(arr.size()) - 1;

        // start with the first element as the minimum
        int minElement = arr[0];

        while (left <= right) {
            const int mid = left + (right - left) / 2;

            // check if the left part is sorted
            if (arr[left] <= arr[mid]) {
                // the equal to is necessary for the case when left == mid
                // if the left part is sorted, the minimum is in the right part
                minElement = min(minElement, arr[left]);
                left = mid + 1;
            } else {
                // if the right part is sorted, the minimum is in the left part
                minElement = min(minElement, arr[mid]);
                right = mid - 1;
            }
        }

        return minElement;
    }
};
