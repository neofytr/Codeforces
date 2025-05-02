#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimum = INT_MAX;

    void solve(const vector<int> &arr, vector<int> &first, vector<int> &second, const int index) {
        if (index >= arr.size()) {
            if (first.size() == arr.size() / 2 && second.size() == arr.size() / 2) {
                const int sum1 = accumulate(first.begin(), first.end(), 0);
                const int sum2 = accumulate(second.begin(), second.end(), 0);
                minimum = min(minimum, abs(sum1 - sum2));
            }
            return;
        }

        if (first.size() < arr.size() / 2) {
            first.push_back(arr[index]);
            solve(arr, first, second, index + 1);
            first.pop_back();
        }

        if (second.size() < arr.size() / 2) {
            second.push_back(arr[index]);
            solve(arr, first, second, index + 1);
            second.pop_back();
        }
    }

    int minimumDifference(const vector<int> &arr) {
        vector<int> first, second;
        solve(arr, first, second, 0);

        // dp solution
    }
};
