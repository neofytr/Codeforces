#include <bits/stdc++.h>
#include <climits>
#include <iomanip>
#include <vector>
using namespace std;

#define int long long

// Problem: vanya
// URL: https://codeforces.com/problemset/problem/492/B
// Difficulty: easy
// Tags:
// Strategy:

bool func(double x, double l, vector<int> &arr) {
    double coverage = 0.0;

    for (int pos : arr) {
        // if this lantern's left bound is beyond current coverage, gap exists
        if (pos - x > coverage)
            return false;

        // extend coverage
        coverage = max(coverage, pos + x);
        if (coverage >= l)
            return true; // already covered till end
    }

    return coverage >= l;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l;
    cin >> n >> l;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // vanya walks late at night along a straight street of length l, lit by n lanterns
    // the coordinate system is such that 0 is the start of the street and l is the end of the street
    // the rth lantern it at the point arr(r)
    // the lantern lights all points of the street that are at a distance of atmost d from it, where d > 0
    // what is the minimum d the lanterns should have to light the whole street
    sort(arr.begin(), arr.end());
    double left = 0;        // can't light the whole street with this
    double right = 2e9 + 1; // can light the whole street with this since the street length can be at most 1e9

    for (int i = 0; i < 100; i++) {
        double mid = left + (right - left) / 2.0;
        if (func(mid, l, arr))
            right = mid;
        else
            left = mid;
    }

    cout << setprecision(12) << right << endl;
    return 0;
}