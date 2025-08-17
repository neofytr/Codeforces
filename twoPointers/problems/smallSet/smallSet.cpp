#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: smallSet
// URL: https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/E
// Difficulty: medium
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

    // a segment [l, r] of the array where 1 <= l <= r < n is good iff there are no more than k unique
    // elements in the segment
    unordered_set<int> seg;
    unordered_map<int, int> mp;
    int cnt = 0;
    int left = 0;
    int right = 0;
    while (left < n) {
        while (right < n && seg.size() + (!mp[arr[right]] ? 1 : 0) <= k) { // does adding the element at right ptr makes the num of unique elements reach the max allowed?
            // if we just do seg.size() < k it will stop when it first reaches k unique elements
            // not taking into account more elements ahead that are equal to previous ones
            // this breaks our invariant

            // seg.size() + (!mp[arr[right]] ? 1 : 0) <= k check if adding the next element will still retain
            // atmost k unique elements or not
            int elt = arr[right];
            mp[elt]++;
            seg.insert(elt);
            right++;
        }

        if (left <= right - 1) {
            // all segments [left, r] where left <= r <= right - 1 are good
            // and they are all the good segments there are starting at left
            cnt += (right - left);
        }

        if (!(--mp[arr[left]]))
            seg.erase(arr[left]);
        left++;
    }
    cout << cnt << endl;
    return 0;
}