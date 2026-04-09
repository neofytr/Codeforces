#include <bits/stdc++.h>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long

// Problem: getTogether
// URL: https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/A
// Difficulty: medium
// Tags:
// Strategy:

bool canMeet(double t, vector<int> &pos, vector<int> &vel) {
    // they all can meet at some point in atmost time t if the following sets have atleast one intersection ->
    // person r can travel atmost in the range [pos[r] - vel[r] * t, pos[r] + vel[r] * t], for any 0 <= r < n

    double left = -1e18, right = 1e18; // meeting points
    for (int i = 0; i < pos.size(); i++) {
        left = max(left, pos[i] - vel[i] * t);
        right = min(right, pos[i] + vel[i] * t);
    }
    return left <= right;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> pos(n);
    vector<int> vel(n);

    for (int i = 0; i < n; i++) {
        cin >> pos[i] >> vel[i];
    }

    // there are n people on a straight line and they need to gather together at one point
    // each person knows his starting position pos[r] and speed vel[r]
    // what is the point x at which they can meet in the minimum time

    // if they all decide to meet at some point y, the time taken by them to meet will be
    // t = max((x - x[r]) / v[r], for all 0 <= r < n)
    // we need to minimize this time

    // one thing to note is that if they all can meet at some point in atmost time t, they all can
    // meet at a point in atmost time z for any z >= t

    // the predicate in this case is
    // f(t) = can they meet at some point in atmost time t (0 if they can't, 1 if they can)
    // as we just noted, f is monotonic

    // if they can meet in atmost time t, and they cannot meet at a point in atmost time y for any y < t
    // then, t is the minimum time in which they can meet at a point

    bool same = true;
    for (int i = 0; i < n - 1; i++) {
        if (pos[i] != pos[i + 1])
            same = false;
    }

    if (same) {
        cout << 0 << endl;
        return EXIT_SUCCESS;
    }

    double left = 0;     // they cannot meet in zero time (except if they all are together)
    double right = 1e13; // they can meet at some point in atmost this much time

    for (int i = 0; i < 100; i++) {
        double mid = left + (right - left) / 2;
        if (canMeet(mid, pos, vel)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << setprecision(16) << right << endl;

    return 0;
}