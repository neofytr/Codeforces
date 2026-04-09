#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;

#define int long long

// Problem: smallSpread
// URL: https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/F
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // all elements of the array are >= 1
    // a segment [l, r] of the array where 1 <= l <= r < n is good iff the difference between the minimum
    // and maximum elements on this segment is at most k

    // we count the num of good segments starting at r for all 0 <= r < n
    // and then add them all

    unordered_map<int, int> mp;
    set<int> seg;
    int left = 0;
    int right = 0;
    int cnt = 0;
    while (left < n) {
        if (right < left)
            right = left;

        while (right < n) {
            int elt = arr[right];
            seg.insert(elt);
            if (*seg.rbegin() - *seg.begin() <= k) {
                mp[elt]++;
                right++;
            } else {
                seg.erase(elt);
                break;
            }
        }

        if (left <= right - 1) {
            // all segments [left, r] where left <= r <= right - 1 are good
            // and they are all the good segments possible starting at left
            cnt += (right - left);
        }

        if (!(--mp[arr[left]]))
            seg.erase(arr[left]);
        left++;
    }
    cout << cnt << endl;
    return 0;
}