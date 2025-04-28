#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int minEatingSpeed(const vector<int> &piles, const int h) {
        int left = 0;
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
