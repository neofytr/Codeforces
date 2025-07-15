#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static bool func(const vector<int> &arr, const int k, const int x) {
        int n = static_cast<int>(arr.size());
        int count = 1; // place first cow at arr[0]
        int last = arr[0];
        for (int index = 1; index < n; index++) {
            if (arr[index] - last >= x) {
                count++;
                last = arr[index];
            }

            if (count == k) {
                return true;
            }
        }

        return false;
    }

    static int aggressiveCows(const vector<int> &arr, const int k) {
        int n = static_cast<int>(arr.size());

        // n >= 2
        // 2 <= k <= n

        sort(arr.begin(), arr.end());

        // arr is in strictly increasing order

        // we have n stalls on a straight line, the position of stall r being arr[r]
        // k is the number of cows we have
        // each stall can have at most one cow
        // we are to assign the cows to stalls such that the minimum distance between the cows is maximized
        // we are to find this max distance

        // if there is an arrangement of cows where the min distance is at least x, then there is an arrangement
        // of cows where the min distance is at least x - 1; for any x > 1

        // if there is no arrangement of cows where the min distance of cows is at least x, there is no arrangement
        // of cows where the min distance is at least x + 1; for any x >= 1

        // define
        // f[x] = 0 if there is an arrangement of cows where the min distance is at least x
        //      = 1 if there is no arrangement of cows where the min distance is at least x

        // f is monotonically increasing

        // we have f[0] = 0 (true for any arrangement)
        // and f(arr.back() - arr.front() + 1) = 1 (since we have to place at least two cows, we can't have at least this much distance between them)

        // thus there is an alpha in the range 0 to arr.back() - arr.front() + 1 such that
        // f[x] = 0 for all x <= alpha
        // f[x] = 1 for all x > alpha

        // now
        // there is an arrangement of cows where the min distance is at least alpha
        // and there is no arrangement of cows where the min distance is at least alpha + 1
        // so the max of min distance is alpha
        // we need to find this alpha

        // we maintain the invariant that
        // f[left] = 0
        // f[right] = 1

        int left = 0;
        int right = arr.back() - arr.front() + 1;

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (func(arr, k, mid)) {
                left = mid;
            } else {
                right = mid;
            }
        }

        return left;
    }
};
