#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static bool canDeliver(const vector<int> &weights, const int days, const long long cap) {
        int dayCount = 1;
        long long currentWeight = 0;

        for (int weight: weights) {
            if (currentWeight + weight > cap) {
                dayCount++;
                currentWeight = weight;

                if (dayCount > days) {
                    return false;
                }
            } else {
                currentWeight += weight;
            }
        }

        return true;
    }

    static int shipWithinDays(const vector<int> &weights, const int days) {
        long long left = *max_element(weights.begin(), weights.end());
        long long right = accumulate(weights.begin(), weights.end(), 0LL);

        while (left < right) {
            const long long mid = left + (right - left) / 2;
            if (canDeliver(weights, days, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return static_cast<int>(left);
    }
};
