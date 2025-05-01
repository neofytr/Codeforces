#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static void loot(const vector<int> &arr, const int index, int &sum, int &max) {
        if (index >= arr.size()) {
            return;
        }

        // we can either loot the current one or choose to skip it

        // loot the current one and move 2 step forward
        sum += arr[index];
        if (max < sum) {
            max = sum;
        }

        loot(arr, index + 2, sum, max);

        // or don't loot the current one and move forward
        sum -= arr[index];
        loot(arr, index + 1, sum, max);
    }

    static int rob(const vector<int> &arr) {
        int max = 0;
        int sum = 0;
        loot(arr, 0, sum, max);

        return max;
    }
};
