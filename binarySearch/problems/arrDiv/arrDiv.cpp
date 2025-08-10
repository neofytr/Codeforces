#include <bits/stdc++.h>
#include <numeric>
#include <vector>
using namespace std;

#define int long long

// Problem: arrDiv
// URL: https://cses.fi/problemset/task/1085
// Difficulty: hard
// Tags:
// Strategy:

bool can(int x, int k, vector<int> &arr) {
    // can we find a divison in which the maximum sum among the divisions is atmost x?
    int divs = 1;
    int sum = 0;
    for (int index = 0; index < arr.size(); index++) {
        if (arr[index] > x)
            return false;

        sum += arr[index];
        if (sum > x) {
            divs++;
            sum = 0;
            index--;
        }
    }

    return divs <= k;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    int sum = 0;
    for (int &val : arr) {
        cin >> val;
        sum += val;
    }

    // we are given an array of length n of positive integers
    // we divide it into k non-empty subarrays and take the maximum of the sums of each of the subarrays
    // we then take the minimum of all of these maximums across all such possible divisions

    // if we can make the maximum sum some atmost x, then we can make it atmost x + 1
    int left = 0;        // we cannot make the maximum sum atmost 0 ever
    int right = sum + 1; // we can make the maximum sum atmost this

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (can(mid, k, arr)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << right << endl;

    return 0;
}