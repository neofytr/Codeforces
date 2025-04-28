#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int singleNonDuplicate(const vector<int> &arr) {
        int left = 0;
        int right = static_cast<int>(arr.size()) - 1;

        while (left <= right) {
            const int mid = left + (right - left) / 2;

            if ((mid == 0 || arr[mid] != arr[mid - 1]) && (mid == arr.size() - 1 || arr[mid] != arr[mid + 1])) {
                return arr[mid];
            }

            if (mid > 0 && arr[mid] == arr[mid - 1]) {
                if (!((mid - 1) & 1) && (mid & 1)) {
                    // if (even, odd),eliminate left
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            if (mid < arr.size() - 1 && arr[mid] == arr[mid + 1]) {
                if (!(mid & 1) && ((mid + 1) & 1)) {
                    // (even, odd), eliminate left
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return 0;
    }
};
