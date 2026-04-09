#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int minEatingSpeed(const vector<int> &piles, const int h) {
        // h >= n

        // if koko can eat all bananas with speed k, she can finish all with speed k + 1; for all k >= 0
        // if koko cannot finish all bananas with speed k, she cannot finish all with speed k - 1; for all k > 0

        // f[k] = 1 ; if koko can finish all bananas with speed k
        //      = 0 ; otherwise if she cannot finish all bananas with speed k

        // f is monotonically increasing
        // f[0] = 0
        // f[max(piles)] = 1

        // so there exists a min k for which f[k] = 1, i.e, there is a k in the range 0 to max(piles) such that
        // f[r] = 0 for all r < k
        // and f[r] = 1 for all r >= k
        // this is what we find with the following binary search

        // we maintain the invariant
        // f[r] = 0 for all r <= left
        // and f[r] = 1 for all r >= right

        // so when right = left + 1, we will have the min k for which f[k] = 1 which will be right

        int left = 1;
        int right = *max_element(piles.begin(), piles.end());

        while (right != left + 1) {
            const int mid = left + (right - left) / 2;
            long long hours = 0;
            for (const int pile: piles) {
                hours += (pile + mid - 1) / mid; // integer ceiling division
                if (hours > h) {
                    break; // early exit
                }
            }
            if (hours <= h) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return right;
    }
};
