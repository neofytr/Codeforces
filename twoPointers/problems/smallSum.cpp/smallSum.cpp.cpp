#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

#define int long long

// Problem: smallSum.cpp
// URL: https://codeforces.com/edu/course/2/lesson/9/2/practice
// Difficulty: easy
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

    // we are to find the length of the longest good segment of the array
    // a segment [l, r] where 0 <= l <= r < n is good iff the sum of the elements in the segment is <= s

    // to find the maximum length good segment
    // we find the maximum length good segment starting at index r for all 0 <= r < n
    // and then take the maximum among those
    int left = 0;
    int right = 0;
    int maxi = LLONG_MIN;
    int sum = 0;
    while (left < n) {
        if (right < left)
            right = left; // we didn't find anything starting at left - 1
        // find the largest good segment starting at index left
        while (right < n && sum + arr[right] <= s)
            sum += arr[right++];

        // the segment [left, right - 1] is good
        if (left <= right - 1) {
            maxi = max(maxi, right - left);
            sum -= arr[left]; // only subtract if arr[left] has been added before
        }
        left++;
    }
    if (maxi == LLONG_MIN)
        cout << 0 << endl;
    else
        cout << maxi << endl;
    return 0;
}