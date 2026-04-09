#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long

// Problem: kthNumUnion
// URL: https://codeforces.com/edu/course/2/lesson/6/5/practice/contest/285084/problem/A
// Difficulty: medium
// Tags:
// Strategy:

bool func(int x, int k, vector<pair<int, int>> &seg) {
    // we are to count the number of elements <= x in the segments
    int count = 0;
    for (auto &[l, r] : seg) {
        if (x < l)
            continue;
        else if (x > r)
            count += (r - l + 1);
        else {
            // x >= l and x <= r
            count += (x - l + 1);
        }
    }

    return count <= k;
}

int32_t main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> segments(n);
    for (auto &[l, r] : segments) {
        cin >> l >> r;
    }

    int left = -2 * 1e9 - 1;
    int right = 2 * 1e9 + 1;

    // we are given n integer segments [l,r]
    // we combine the segments into a single sorted array
    // we are to find the element at the kth index in the sorted array

    // we define
    // count(x) = number of elements <= x in the final array
    // f(x) = 1 if count(x) <= k
    //      = 0 otherwise

    // we find the element m such that f(m) = 1 and f(m + 1) = 0
    // this implies that m is the element at the kth index in the final array

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (func(mid, k, segments))
            left = mid;
        else
            right = mid;
    }

    cout << right << endl;
    return EXIT_SUCCESS;
}