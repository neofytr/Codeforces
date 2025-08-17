#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

#define int long long

// Problem: bigSum
// URL: https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    cin >> n >> s;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // all array values are non-negative
    // a segment [l,r] where 0 <= l <= r < n is good iff its sum is atleast s
    // we are to find the shortest good segment

    // we find the shortest good segment starting at index r for every 0 <= r < n and then
    // take the minimum of all of them

    int minLen = LLONG_MAX;
    int left = 0;
    int right = 0;
    int sum = 0;
    while (left < n) {
        if (right < left)
            right = left;
        while (right < n && sum < s)
            sum += arr[right++]; // if the current sum is less than s, add the current right ptr element

        if (left <= right - 1) {
            // [left, right - 1] is a good segment
            minLen = min(minLen, right - left);
            sum -= arr[left];
        }
        left++;
    }

    if (minLen == LLONG_MAX)
        cout << -1 << endl;
    else
        cout << minLen << endl;
    return 0;
}