#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: knapsackSegment
// URL: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/E
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    cin >> n >> s;

    vector<int> wts(n);
    for (int &val : wts)
        cin >> val;
    vector<int> cost(n);
    for (int &val : cost)
        cin >> val;

    // we are given an array of n items, for each them it's weight is wts[r] and cost is cost[r]
    // we need to select a segment of this array, the total weight on which is not more than s, and the
    // total cost is maximum

    // there is subsegment monotonicity in this
    // for each r,
    // we can find tmin; tmax = r
    // since all the costs are positive, the take the segment [tmin, tmax] as the segment ending at r
    // with total weight <= s with the maximum cost among all those ending at r with total weight <= s

    int ans = LLONG_MIN;
    int w = 0;
    int c = 0;
    int left = 0;
    for (int right = 0; right < n; right++) {
        w += wts[right];
        c += cost[right];
        while (left <= right && w > s) {
            c -= cost[left];
            w -= wts[left++];
        }
        if (left <= right) {
            // we now have [tmin, tmax = r]
            ans = max(ans, c);
        }
    }
    if (ans == LLONG_MIN)
        ans = 0;
    cout << ans << endl;
    return 0;
}