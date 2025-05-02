#include <bits/stdc++.h>
using namespace std;

#define MAX_TARGET (200 * 100)

class Solution {
public:
    static bool canPartition(const vector<int> &arr) {
        const int total = accumulate(arr.begin(), arr.end(), 0);
        if (total & 1) return false;

        bitset<MAX_TARGET + 1> reachable;
        reachable.set(0);

        for (const int num: arr) {
            reachable |= (reachable << num);
            if (reachable[total / 2]) {
                return true; // early stop
            }
        }

        return false;
    }
};
