#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static bool func(const vector<int> &arr, const int k, const int max) {
        const int n = static_cast<int>(arr.size());
        // we want to check if we can split such that the largest sum is at most x

        int count = 1;
        int curr = 0;

        for (int index = 0; index < n; index++) {
            if (arr[index] > max) {
                return false; // we can never split in this case
            }

            if (curr + arr[index] > max) {
                curr = 0;
                count++;
                index--;
            } else {
                curr += arr[index];
            }

            if (count > k) {
                return false;
            }
        }

        return true;
    }

    static int splitArray(const vector<int> &arr, const int k) {
        int n = static_cast<int>(arr.size());

        // n >= 1
        // 1 <= k <= n

        // if n == 1, then k == 1
        if (n == 1) {
            return arr[0];
        }

        // given an integer array arr and an integer k
        // split arr into k non-empty subarrays such that the
        // largest sum of any subarray is minimized

        // return the minimized largest sum of the split
        // a subarray is a contiguous part of the array

        // if there is a division where the largest sum is at most x, then there is a division
        // where the largest sum is at most x + 1; for all x >= 0

        // if there is no division where the largest sum is at most x, then there is no division
        // where the largest sum is at most x - 1; for all x >= 1

        // define
        // f[x] = 1 if there is a division where the largest sum is at most x
        //      = 0 if there is no division where the largest sum is at most x

        // f[0] = 0
        // f[1] = sum of all elements in the array

        // f is monotonically increasing
        // so there is an alpha such that
        // f[x] = 0 for all x < alpha
        // and f[x] = 1 for all x >= alpha

        // thus, there is a division where the largest sum is at most alpha, but there is no
        // division where the largest sum is at most x for any x < alpha
        // thus alpha is the minimum we are looking for

        // we maintain the invariant
        // f[left] = 0
        // f[right] = 1

        int left = 0;
        int right = accumulate(arr.begin(), arr.end(), 0);

        while (right != left + 1) {
            const int mid = left + (right - left) / 2;
            if (func(arr, k, mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }

        return right;
    }
};
