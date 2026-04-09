#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: numSmallSum
// URL: https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/C
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

    // all elements of the array are >= 1
    // a segment [l,r] of the array where 1 <= l <= r < n is good iff the sum of the elements in this segment is atmost s
    // we are to count the number of such good segments

    // we count the number of segments starting at index r for each 0 <= r < n, and all them all
    int cnt = 0;
    int sum = 0;
    int left = 0;
    int right = 0;
    while (left < n) {
        if (right < left)
            right = left;
        while (right < n && sum + arr[right] <= s)
            sum += arr[right++];

        if (left <= right - 1) {
            // [left, right - 1] is a good segment along with any
            // subsegment of this that starts at left
            // so, total num of good segments starting at left = (right - left)
            cnt += (right - left);
            sum -= arr[left];
        }
        left++;
    }
    cout << cnt << endl;
    return 0;
}