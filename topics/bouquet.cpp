#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static bool canMake(const vector<int> &bloomDay, int days, int m, int k) {
        int bouquets = 0, flowers = 0;
        for (const int bloom: bloomDay) {
            if (bloom <= days) {
                if (++flowers == k) {
                    bouquets++;
                    flowers = 0;
                }
            } else {
                flowers = 0;
            }
        }
        return bouquets >= m;
    }

    static int minDays(const vector<int> &bloomDay, int m, int k) {
        const int n = static_cast<int>(bloomDay.size());
        if (1LL * m * k > n) return -1;

        int left = 0, right = *max_element(bloomDay.begin(), bloomDay.end());

        while (left + 1 != right) {
            const int mid = left + (right - left) / 2;
            if (canMake(bloomDay, mid, m, k)) {
                right = mid;
            } else {
                left = mid;
            }
        }

        return right;
    }
};
